main :: IO ()
main = do
 x1 <- readLn -- this is a
 x2 <- readLn -- this is b
 putStrLn (show (find x1 x2 0))

lenn :: String -> Int
lenn [] = 0
lenn (x:y) = 1 + lenn y

find0 :: String -> String -> Bool
find0 y [] = True
find0 (x:y) (m:n) = if (x==m) then find0 y n
				else False

find :: String -> String -> Int -> Int
find (x:y) n xx = if (lenn (x:y) < lenn n) then -1
				else if (find0 (x:y) n) then xx
				else find y n (xx+1)
