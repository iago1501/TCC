setwd("/home/raphael/Documents/trabalho/R scripts")


v1 <- runif(100, min = 1, max = 20)
v2 <- runif(100, min = 1, max = 20)

index_menor <- which(v1<v2)

index_maior <- which(v1>v2)

speedup <- c( - v2[index_menor] / v1[index_menor], v1[index_maior] / v2[index_maior])

yn <- speedup[speedup<0] + 1

yp <- speedup[speedup>0] - 1




yn <- yn[order(yn)]
yp <- yp[order(yp)]

xn <- 1:length(yn)
xp <- (length(yn)+1):(length(yn)+length(yp))

yrange <- ceiling(max(-min(yn),max(yp)))



pdf("graph.pdf", width = 9, height = 5)

plot(xn, yn, axes = F, xlim = range(1:(length(yn)+length(yp))), ylim = range(-yrange:yrange), type = 'h', lty = 3, ylab = "Speed-up (x)", xlab = "")
lines(c(max(xn), xp), c(max(yn),yp), type = 'h', lty = 3)

lines(xn, yn, type = 'l', lty = 1)
lines(c(max(xn), xp), c(max(yn),yp), type = 'l', lty = 1)

#points(xn, yn, pch = 18)
#points(xp, yp, pch = 18)

poslabel <- seq(1,yrange,length.out=4)
neglabel <- -poslabel[length(poslabel):2]
poslabel <- round(poslabel, digits=2)
neglabel <- round(neglabel, digits=2)
axis(side = 2, las = 2, at = seq(-yrange,yrange,length.out=7), labels = c(neglabel, poslabel) )

abline(h = 0)

abline(v = length(yn) + 1 - min(yp)/(min(yp)-max(yn)), lty = 6, lwd = 3, col = 'red')

text( length(xn)/2, yrange/2, adj = c(0.5,0.5), labels = paste(round(100*length(yn)/(length(yn)+length(yp)), digits = 2),"%") )

text( length(xn) + length(xp)/2, -yrange/2, adj = c(0.5,0.5), labels = paste(100-round(100*length(yn)/(length(yn)+length(yp)), digits = 2),"%"))

dev.off()

