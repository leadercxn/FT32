/**
  @page OPA/OPA_EXAMPLE example
  
  

@par How to use it ? 

PA9 IS USART TX
OPA amplify K=(1+40/4)=11
PA1 IS +
PA0 IS OUT
PA7 IS ADCINPUT,   SO , CONNECT PA0 TO PA7 , THE OPA OUTPUT PA0 CAN BE READ BY ADC

if PA1=0.252V,  then PA0=0.252*11=2.772,  so the usart send "ADC_VALUE 2.772" by pin PA9 