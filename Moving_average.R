moving_average <- function(x, n){
  filter(x, rep(1,n)) / n
}

cs<-read.table("C:/Users/ito/Desktop/‰·Ž¼“x/export/No.4.csv",header = T,sep=",")

temp<-as.numeric(cs[1,])
hum<-as.numeric(cs[2,])

width<-20

result.temp<-moving_average(temp,width)
result.hum<-moving_average(hum,width)

plot(1:length(temp),temp,type="l",xlab="",ylab = "",col='blue'
     ,panel.first = grid(NA, NULL, lty = 2, col = "#E9DECA"))
par(new =T)
plot(1:length(temp),result.temp,type="l",xlab="time[s]",ylab = "blue=temp, red=MA"
     ,axes = FALSE,col='red')

plot(1:length(hum),hum,type="l",xlab="",ylab = "",col='blue'
     ,panel.first = grid(NA, NULL, lty = 2, col = "#E9DECA"))
par(new =T)
plot(1:length(hum),result.hum,type="l",xlab="time[s]",ylab = "blue=hum, red=MA"
     ,axes = FALSE,col='red')
