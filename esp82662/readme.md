AT+CWJAP="belkin.feb","fa494fd7"
AT+CIPMUX=0
AT+CIPSTART="TCP","api.thingspeak.com",80

AT+CIPSEND=51

GET /update?api_key=PCS1W76A236K0HKW&field1=255
AT+CIPCLOSE
