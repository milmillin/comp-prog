fibo n = if n==1 then 1 
	else if n==2 then 1
	else fibo (n-1) + fibo(n-2)

fibo2 1=1
fibo2 2=1
fibo2 n=fibo(n-1)+fibo(n-2)

len [] = 0
len (_:xs) = 1 + len xs

ll 0 = []
ll x = x:(ll (x-1))

summ [] = 0
summ (x:y) = x + summ y

myappend x [] = [x]
myappend x (y:z) = (y:(myappend x z))

myconcat [] z = z
myconcat (x:y) z = x:(myconcat y z)

insertt [] z = [z]
insertt (x:y) z = if (x<z) then x:(insertt y z)
	else z:(x:y)

isort [] = []
isort (x:y) = insertt (isort y) x


revv [] z = z
revv (x:y) z = revv y (x:z)

rev x = revv x []

lsplit0 [] l a b = (a,b)
lsplit0 (x:y) l a b = if ((mod l 2)==1) then lsplit0 y (l-1) (x:a) b
	else lsplit0 y (l-1) a (x:b)

lsplit x = lsplit0 x (len x) [] []

mrg [] [] = []
mrg m [] = m
mrg [] n = n
mrg (x:y) (m:n) = if (x<m) then (x:(mrg y (m:n))) else (m:(mrg (x:y) n))

msort [] = []
msort [xx] = [xx]
msort x = mrg (msort a) (msort b) where (a,b)=lsplit x


isSorted :: [Int] -> Bool
-- Write your code here'
isSorted [x] = True
isSorted (x:y:z) = if (x<=y) then isSorted (y:z)
		else False
