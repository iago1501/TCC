#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

y <- read.table(args[1], header = T)
y <- y[order(y[,1]),]

pdf(args[2], width = 9, height = 5)

plot(y[600:1000,2],log = "y", pch = 20, xlab = "Experimentos ordenados por quantidade de offsets testados", ylab = "Tempo em milissegundos")
lines(y[600:1000,as.numeric(args[4])], type = "l")
legend("topleft", legend = c("Força Bruta", args[3]), lty=c(NA,1), pch=c(20,NA))

dev.off()

