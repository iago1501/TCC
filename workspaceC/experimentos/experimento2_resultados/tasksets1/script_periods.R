y <- read.table("experiment2_tasksets1_exectime.txt", header = T)


plot(sort(y[,4]), log="y", type = "l", lty = 1)
lines(sort(y[,3]),  log="y", lty = 2)
lines(sort(y[,2]),  log="y", lty = 3)
lines(sort(y[,1]),  log="y", lty = 4)

