# Usage: `testing_tool.py test_number`, where the argument test_number
# is 0 for Test Set 1 or 1 for Test Set 2.

from __future__ import print_function
import random
import sys
import re
import subprocess

"""Helper functions"""
def JudgePrint(p, s):
  # Print the judge output to your code's input stream. Log this interaction
  # to console (stdout) if PRINT_INTERACTION_HISTORY is True.
  print(s, file=p.stdin)
  p.stdin.flush()
  print("Judge prints:", s)


def PrintSubprocessResults(p):
  # Print the return code and stderr output for your code.
  print("Your code finishes with exit status {}.".format(p.returncode))


def WaitForSubprocess(p):
  # Wait for your code to finish and print the stderr output of your code for
  # debugging purposes.
  if p.poll() is None:
    print("Waiting for your code to finish...")
    p.wait()
  PrintSubprocessResults(p)


def CheckSubprocessExit(p, case_id):
  # Exit if your code finishes in the middle of a test case.
  if p.poll() is not None:
    print("Your code exited early, in the middle of Case #{}.".format(case_id))
    PrintSubprocessResults(p)
    sys.exit(-1)


# Use raw_input in Python2.
try:
  input = raw_input
except NameError:
  pass

_ERROR_MSG_EXTRA_NEW_LINES = "Input has extra newline characters."
_ERROR_MSG_INCORRECT_ARG_NUM = "Answer has wrong number of tokens."
_ERROR_MSG_NOT_SORTED = "Worker IDs in answer must be sorted."
_ERROR_MSG_NOT_UNIQUE = "Worker IDs in answer must be distinct."
_ERROR_MSG_INVALID_TOKEN = "Input has invalid token."
_ERROR_MSG_OUT_OF_RANGE = "Input includes an out-of-range value."
_ERROR_MSG_READ_FAILURE = "Read for input fails."

_QUERY_LIMIT_EXCEEDED_MSG = "Query Limit Exceeded."
_WRONG_ANSWER_MSG = "Wrong Answer."

_ERROR_MSG_INTERNAL_FAILURE = ("The judge failed due to an internal error. "
                               "This should not happen, please raise an issue "
                               "to the Code Jam team.")


class Case:

  def __init__(self, bad_set, N, F):
    self.__bad_set = set(bad_set) # The set of broken computers
    self.__N = N # The total number of computers
    self.__max_num_tries = F # The number of allowed guesses
    self.__raw_input = input

  def getBadSet(self):
    return self.__bad_set;

  def _parse_contestant_query(self, bitstring):
    """Tries to parse a contestant's input as if it were a query bitstring.

    Returns:
      (string, string): The first argument is the bitstring, the second is
      the error string in case of error.
      If the parsing succeeds, the return value should be (str, None).
      If the parsing fails, the return value should be (None, str).
    """
    # Must be of length exactly N
    if len(bitstring) != self.__N:
      return (None, _ERROR_MSG_INVALID_TOKEN)
    # Bitstring must contain only 0 and 1
    if not all([x in '01' for x in bitstring]):
      return (None, _ERROR_MSG_INVALID_TOKEN)
    return (bitstring, None)

  def _parse_contestant_answer(self, tokens):
    """Tries to parse a contestant's input as if it were answering a testcase.

    Returns:
      (list string): The first argument is the answer, the second is
      the error string in case of error.
      If the parsing succeeds, the return value should be (list, None).
      If the parsing fails, the return value should be (None, str).
    """
    if len(tokens) != len(self.__bad_set):
      return (None, _ERROR_MSG_INCORRECT_ARG_NUM)
    try:
      contestant_answer = list(map(int, tokens))
    except Exception:
      return (None, _ERROR_MSG_INVALID_TOKEN)

    if sorted(contestant_answer) != contestant_answer:
      return (None, _ERROR_MSG_NOT_SORTED)

    if len(set(contestant_answer)) != len(contestant_answer):
      return (None, _ERROR_MSG_NOT_UNIQUE)

    for x in contestant_answer:
      if (x < 0) or (x >= self.__N):
        return (None, _ERROR_MSG_OUT_OF_RANGE)

    return (contestant_answer, None)


  def _parse_contestant_input(self, response):
    """Parses contestant's input.

    Parse contestant's input which should be either a string of N bits or
    a list of len(bad_set) space-separated integers.

    Args:
      response: (str or list) one-line of input given by the contestant.

    Returns:
      (int or list, string): The bitstring sent by the contestant if making
      a query, or a list of ints if the contestant is answering the test case.
      the second argument is an error string in case of error.
      If the parsing succeeds, the return value should be (int or list, None).
      If the parsing fails, the return value should be (None, str).
    """
    if ("\n" in response) or ("\r" in response):
      return None, _ERROR_MSG_EXTRA_NEW_LINES
    if not re.match("^[\s0-9-]+$", response):
      return None, _ERROR_MSG_INVALID_TOKEN
    tokens = response.split()
    if len(tokens) == 1 and len(tokens[0]) == self.__N:
      # If there is exactly one token and it has length N, it must be a query.
      # A number with N digits has to be at least 10**N which is always > N,
      # so there is no way for a valid answer to be mistaken as a query.
      return self._parse_contestant_query(tokens[0])
    else:
      # It's not a query, so it must parse as an answer.
      return self._parse_contestant_answer(tokens)

  def _answer_query(self, bitstring):
    answer = ""
    for i in range(self.__N):
      if i not in self.__bad_set:
        answer += bitstring[i]
    return answer

  def Judge(self, p):
    """Judge one single case; should only be called once per test case.

    Returns:
      An error string, or None if the attempt was correct.
    """

    JudgePrint(p, ' '.join([str(self.__N), str(len(self.__bad_set)), str(self.__max_num_tries)]))

    # +1 for the answer they have to give
    for queries in range(self.__max_num_tries + 1):
      try:
        #contestant_input = self.__raw_input()
        contestant_input = p.stdout.readline()
        contestant_input = contestant_input[:-1]
        print("received ", contestant_input)
      except Exception:
        return _ERROR_MSG_READ_FAILURE
      contestant_input, err = self._parse_contestant_input(contestant_input)
      if err is not None:
        return err
      if type(contestant_input) is str:
        # Query
        if queries == self.__max_num_tries:
          # Too many queries
          return _QUERY_LIMIT_EXCEEDED_MSG
        else:
          JudgePrint(p, self._answer_query(contestant_input))
      else:
        # Answer
        assert(type(contestant_input) is list)
        if set(contestant_input) == self.__bad_set:
          # Testcase answered correctly
          JudgePrint(p, 1)
          return None
        else:
          return _WRONG_ANSWER_MSG
    return _QUERY_LIMIT_EXCEEDED_MSG

def getTestCases(test_number):
  F = (10, 5)[test_number]
  # You can edit or add your own test cases here.
  cases = [Case([1, 2, 3], 4, F), 
          Case([2, 3, 5], 6, F),
          Case([0, 3], 5, F),
          Case([1000], 1024, F),
          Case(range(15), 100, F),
          Case(range(14), 100, F),
          Case(range(13), 100, F),
          Case(range(12), 100, F),
          Case(range(11), 100, F),
          Case(range(10), 100, F),
          Case(range(9), 100, F),
          Case(range(8), 100, F),
          Case(range(7), 100, F),
          Case(range(6), 100, F),
          Case(range(5), 100, F),
          Case(range(4), 100, F),
          Case(range(3), 100, F),
          Case(range(2), 100, F),
          Case([0], 100, F),
          Case([i + 253 for i in range(15)], 300, F),
          Case([i + 254 for i in range(15)], 300, F),
          Case([i + 255 for i in range(15)], 300, F),
          Case([i + 256 for i in range(15)], 300, F),
          Case([i + 257 for i in range(15)], 300, F),
          Case([i + 258 for i in range(15)], 300, F),
          Case([i + 259 for i in range(15)], 300, F),
          Case([i + 260 for i in range(15)], 300, F),
          Case([i + 261 for i in range(15)], 300, F),
          Case([i + 262 for i in range(15)], 300, F),
          Case([i + 263 for i in range(15)], 300, F),
          Case([i + 264 for i in range(15)], 300, F),
          Case([i + 265 for i in range(15)], 300, F),
          Case([i + 266 for i in range(15)], 300, F),
          Case([i + 267 for i in range(15)], 300, F),
          Case([i + 268 for i in range(15)], 300, F),
          Case([i + 253 for i in range(3)], 300, F),
          Case([1019, 1020, 1021, 1022, 1023], 1024, F),
          Case([1, 10, 100, 234, 293, 102, 103, 399], 1024, F),
          Case([1023 - i for i in range(15)], 1024, F),
          Case([1020, 1021, 1022, 1023], 1024, F)]
  
  extra = [Case([i + j for i in range(k)], 1024, F) for k in range(1, 15) for j in range(16)]

  cases.extend(extra)

  return cases


def JudgeAllCases(p):
  """Sends input to contestant and judges contestant output.

  In the case of any error (other than extra input after all testcases are
  finished), -1 is printed to stdout.

  Returns:
    An error string, or None if the attempt was correct.
  """
  cases = getTestCases(1)

  JudgePrint(p, len(cases))
  for idx, case in enumerate(cases):
    err = case.Judge(p)
    if err is not None:
      JudgePrint(p, -1)
      return "Case #{} fails:\n{} {}".format(idx+1, err, case.getBadSet())

  extra_output = p.stdout.readline()
  WaitForSubprocess(p)
  print("yay ", extra_output)

def startProcess():
    try:
      p = subprocess.Popen(
          sys.argv[1:],
          stdin=subprocess.PIPE,
          stdout=subprocess.PIPE,
          stderr=sys.stderr,
          bufsize=1,
          universal_newlines=True)
      return p
    except Exception as e:
      print("Failed to start running your code. Error:")
      print(e)
      sys.exit(-1)

def main():
  random.seed(379009)
  result = JudgeAllCases(startProcess())
  if result is not None:
    print(result, file=sys.stderr)
    sys.exit(1)


if __name__ == "__main__":
  main()

