#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

mydata <- read.table(args[3], header = T)

v1 <- mydata[,as.numeric(args[1])]
v2 <- mydata[,as.numeric(args[2])]

index_menor <- which(v1<v2)

index_maior <- which(v1>v2)

speedup <- c( v2[index_menor] / v1[index_menor], - v1[index_maior] / v2[index_maior])

yn <- speedup[speedup<0]
yp <- speedup[speedup>0]



yn <- yn[order(yn)]
yp <- yp[order(yp)]


xn <- 1:length(yn)
xp <- (length(yn)+1):(length(yn)+length(yp))

yrange <- ceiling(max(-min(yn),max(yp)))


#adapting for logscale
logyrange <- log(ceiling(max(-min(yn),max(yp))))
yn <- yn
yp <- yp



pdf(args[4], width = 9, height = 5)
par(mar = c(3,6,1,1), mgp = c(1,1,0))

plot(xn, -log(-yn), axes = F, xlim = range(1:(length(yn)+length(yp))), ylim = c(-logyrange,logyrange), type = 'h', lty = 3, ylab = "", xlab = "Experiment", main = args[4])
lines(c(max(xn), xp), c(-log(-max(yn)),log(yp)), type = 'h', lty = 3)

lines(xn, -log(-yn), type = 'l', lty = 1)
lines(c(max(xn), xp), c(-log(-max(yn)),log(yp)), type = 'l', lty = 1)

#points(xn, yn, pch = 18)
#points(xp, yp, pch = 18)

posloglabel <- exp(1)^seq(0,logyrange,length.out=4)
negloglabel <- -posloglabel[length(posloglabel):2]

#posloglabel <- formatC(posloglabel, format = 'e', digits=2)
#negloglabel <- formatC(negloglabel, format = 'e', digits=2)

posloglabel <- round(posloglabel, digits=2)
negloglabel <- round(negloglabel, digits=2)

title(mgp = c(4,1,0), ylab = "Speed-up (x)")
axis(side = 1, pos = 0, xaxp = c(1,length(c(xn,xp)),10), labels = F, tcl = 0.5)
axis(side = 1, pos = 0, xaxp = c(1,length(c(xn,xp)),10), labels = F, tcl = -0.5)
axis(side = 1, pos = 0, xaxp = c(1,length(c(xn,xp)),20), labels = F, tcl = 0.25)
axis(side = 1, pos = 0, xaxp = c(1,length(c(xn,xp)),20), labels = F, tcl = -0.25)
axis(side = 2, las = 2, at = seq(-logyrange,logyrange,length.out=7), labels = c(negloglabel,posloglabel))

#abline(h = 0)

abline(v = length(yn) + 1 - min(yp)/(min(yp)-max(yn)), lty = 6, lwd = 3, col = 'red')

text( length(xn)/2, logyrange/2, adj = c(0.5,0.5), labels = paste(round(100*length(yn)/(length(yn)+length(yp)), digits = 2),"%") )
text( length(xn) + length(xp)/2, -logyrange/2, adj = c(0.5,0.5), labels = paste(100-round(100*length(yn)/(length(yn)+length(yp)), digits = 2),"%"))


areap <- tail(cumsum(yp[-length(yp)]*diff(xp) + diff(yp)*diff(xp)/2), n = 1)
text(tail(xp, n = 1), tail(log(yp),n=1), adj = c(1,0), paste("Area = ",round(areap, digits = 2)))


arean <- tail(-cumsum(yn[-length(yn)]*diff(xn) + diff(yn)*diff(xn)/2), n = 1)
text(1, -log(-yn[1]), adj = c(0,1), paste("Area = ",round(arean, digits = 2)))


dev.off()

