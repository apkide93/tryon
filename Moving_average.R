moving_average <- function(x, n){
  filter(x, rep(1,n)) / n
}

cs<-read.table("C:/Users/ito/Desktop/‰·Ž¼“x/export/No.3.csv",header = T,sep=",")

temp<-as.numeric(cs[1,])
hum<-as.numeric(cs[2,])

width<-60

result.temp<-moving_average(temp,width)
result.hum<-moving_average(hum,width)

plot(1:length(temp),result.temp,type="l")
plot(1:length(hum),result.hum,type="l")
