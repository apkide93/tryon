cliarg = commandArgs(TRUE)

s1<-as.numeric(cliarg[1])
s2<-as.numeric(cliarg[2])
s3<-as.numeric(cliarg[3])
s4<-as.numeric(cliarg[4])
s5<-as.numeric(cliarg[5])
s6<-as.numeric(cliarg[6])
s7<-as.numeric(cliarg[7])
s8<-as.numeric(cliarg[8])
s9<-as.numeric(cliarg[9])
s10<-as.numeric(cliarg[10])
e1<-as.numeric(cliarg[11])
e2<-as.numeric(cliarg[12])
e3<-as.numeric(cliarg[13])
e4<-as.numeric(cliarg[14])
e5<-as.numeric(cliarg[15])
e6<-as.numeric(cliarg[16])
e7<-as.numeric(cliarg[17])
e8<-as.numeric(cliarg[18])
e9<-as.numeric(cliarg[19])
e10<-as.numeric(cliarg[20])


#‰ŠúÝ’è
max<-as.numeric(cliarg[21])
s<-c(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10)
e<-c(e1,e2,e3,e4,e5,e6,e7,e8,e9,e10)

#‰ŠúW’cì¬
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

for (lgene in 1:200) {
  for (sgene in 1:30) {
    
    #•]‰¿
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
    
    #Œð³
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
    
  }
  
  #“Ë‘R•ÏˆÙ
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

#Œ‹‰Ê

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
