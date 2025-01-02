# Project md_recorder

A project desgined to record market data

## Prerequisite

[v6.7.2_traderapi_20230913.zip](http://www.sfit.com.cn/5_2_DocumentDown_2_2.htm)

## Calendar File

a text file contains trade date of futures. format like

```csv
trade_date
20080102
20080103
20080104
20080107
20080108
...
20251225
20251226
20251229
20251230
20251231
```

## md.conf

format like

```txt
calendarPath=/mnt/data/trade/calendar/cne_calendar.csv
accountFilePath=/home/ubuntu/deploy/account_md
mdSaveRootDir=/mnt/data/trade/ticks
subscribedFile=subscribed
```

## Account File

a text file, first line begin with "#", and program will skip it. It includes the following
variables:

+ active: Please **set 'active' = 1 to activate the account**, the first row of with 'active = 1' will be used.
+ linkMode: "REAL" or "SIMU"
+ frontAddr: like "tcp://116.236.253.145:42213"
+ brokerId: like "95533", ask your broker.
+ invstrId: your user name
+ password: your password
+ appId: your client name
+ authCode: your authentic code
+ consPath: set the cons path
