#初期設定
max<-123
s<-c(37,28,3,57,12,33,21,48,28,9)
e<-c(8,4,3,7,5,4,2,10,6,3)

lgenemax<-600
sgenemax<-20

gra.s<-c()
gra.e<-c()


#初期集団作成
x<-runif(200)
for (lo in 1:200) {
  if (x[lo] < 0.5) {
    x[lo]<-0
  }
  else {
    x[lo]<-1
  }
}

x<-matrix(x,20,10)

for (lgene in 1:lgenemax) {
for (sgene in 1:sgenemax) {

#評価
ssum<-0
esum<-0
for (lo in 1:10) {
  if (x[1,lo] == 1) {
    ssum<-ssum+s[lo]
    esum<-esum+e[lo]
  }
}
slist<-ssum
elist<-esum

for (lo1 in 2:20) {
  ssum<-0
  esum<-0
  for (lo2 in 1:10) {
    if (x[lo1,lo2] == 1) {
      ssum<-ssum+s[lo2]
      esum<-esum+e[lo2]
    }
  }
  slist<-c(slist,ssum)
  elist<-c(elist,esum)
}

for (lo in 1:20) {
  if (slist[lo] > max) {
    elist[lo]<-0
  }
}

for (lo1 in 1:20) {
for (lo in 1:19) {
if ( elist[lo] < elist[lo+1]) {
  etmp<-elist[lo]
  elist[lo]<-elist[lo+1]
  elist[lo+1]<-etmp
  
  stmp<-slist[lo]
  slist[lo]<-slist[lo+1]
  slist[lo+1]<-etmp
  
  xtmp<-x[lo,]
  x[lo,]<-x[lo+1,]
  x[lo+1,]<-xtmp
}
}
}

#交叉
for (lo in 1:5) {
  lo1<-2*lo-1
  for (lo2 in 1:5) {
    x[lo+10,lo2]<-x[lo1,lo2]
  }
  for (lo2 in 6:10) {
    x[lo+10,lo2]<-x[lo1+1,lo2]
  }
}

for (lo in 1:5) {
  lo1<-2*lo
  for (lo2 in 1:5) {
    x[lo+15,lo2]<-x[lo1,lo2]
  }
  for (lo2 in 6:10) {
    x[lo+15,lo2]<-x[lo1-1,lo2]
  }
}


#グラフ作成用変数
gra.s<-c(gra.s,slist[1])
gra.e<-c(gra.e,elist[1])

}

#突然変異
y<-runif(10)
for (lo in 1:10) {
  if (y[lo] < 0.5) {
    y[lo]<-0
  }
  else {
    y[lo]<-1
  }
}

for (lo in 1:10) {
  x[20,lo]<-y[lo]
}


}

#結果

res<-c()
for (lo in 1:10) {
  if (x[1,lo] == 1) {
    res[lo]<-s[lo]
  }
  else {
    res[lo]<-0
  }
}

res
slist[1]
elist[1]

genemax<-lgenemax * sgenemax
gra.x<-1:genemax
plot(gra.x, gra.s,type="l",col=rgb(0,0,1))
plot(gra.x, gra.e,type="l",col=rgb(1,0,0))
