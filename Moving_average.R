moving_average <- function(x, n){
  filter(x, rep(1,n)) / n
}

date<-c(1,2,3,4,5,6,7,8,9,10)
datas<-c(1,3,5,6,2,12,3,5,6,1)
width<-3

result<-moving_average(datas,width)

result

plot(date,result,type="l")
