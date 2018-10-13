n = 20
step = (4 - 2) / 19
a1 = seq(2, 4, step)
a1

a2 = sample(seq(3, 14, 1), 10, TRUE)
a2

a3 = c()
for (i in 1:6) {
  elem = readline(paste("a3[", i, "] = "))
  a3[i] = strtoi(elem)
}
a3

a4 = c(a3, a2)
a4

a1[2] * a2[3]


x = scan("~/Dev/labs/r-labs/1.txt", what = numeric())
x

t(x) %*% a1

which.min(x)
min(x)

x
sum(x >= 8 & x <= 10)

m1 = scan("~/Dev/labs/r-labs/2.txt", what = numeric())
m1 = matrix(m1, nrow = 4)
m1

m2 = sample.int(16, 16)
m2 = matrix(m2, nrow=4)
m2

m1 + m2
m1 %*% m2

det(m2)
det(m1)

solve(m1, c(1, 0, -1, 2))


nrow = 1:15
names = c('lol', 'kek', 'chebureck', 'lal', 'lil', 'lel', 'lul', 'lvl 80', 'r', 'fartu', 'masti', 'aue', 'vecher', 'v', 'hatu')
births = runif(15, 1960, 1985)
births = as.integer(births)

employYear = c()
for (b in births) {
  employYear = c(employYear, runif(1, b+18, 2006))
}
employYear = as.integer(employYear)

older1975 = births >= 1975
salaries1 = (log(2007 - employYear) + 1) * 8000
salaries2 = (log2(2007 - employYear) + 1) * 8000

salaries = salaries1 * (1-older1975) + salaries2 * older1975

data.frame(nrow, names, births, employYear, salaries)
