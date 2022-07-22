Dionysios Mpentour 1115201300115

To programma apoteleitai apo 3 arxeia ta opoia einai
chef.c
saladmaker.c
Makefile


Kata thn ekinnisi tou programmatos dimiourgeitai to shared memory segment
to opoio exei mege8os sizeof(int)+ 4*sizeof(sem_t) sto opoio apo8ikeuetai 
o ari8mos twn salatwn kai oi 4 simaforoi, pou xrisimopoiountai gia tin
omali ektelesi twn 4 programmatwn.

To id tou Shared Memory Segement pernietai ws argument prin thn ektelesi twn 
saladmaker.

I dimiourgia kai arxikopoihsh twn semaphore ginetai apo ton chef ka8ws kai i 
katastrofi tous + tou shared memory.

Arxika o chef epilegei tuxaia 2 ulika kai stelnei sima ston antistoixo saladmaker
na paralabei ta ulika. Stin sunexeia ginetai block mexri o saladmaker na oloklirwsei
tin salata kai na labei to post wste na epile3ei epipleon 2 ulika kai na epanalabei 
tin diadikasia mexri na teleiwsoyn oi salates pou exoun ziti8ei.

Uparxei ena eniaio logfile sto opoio grafei o chef kai oi 3 saladmaker. O ka8e 
saladmaker dimiourgei episis ena monadiko logfile pou anaferei pote dimiourgise tin
salata.

Den exei ulopoih8ei swsta to output tou chef ka8ws oi salates poy dimiourgei o ka8e
saladmaker den perniountai sthn shared memory alla tupwnontai apo ton idio. 

Ousiastika i ka8e diergasia trexei seiriaka, afou mexri na oloklirwsei tin drasi tis 
oi upoloipes einai blocked apo ton semaphore tous.

Episis uparxei ena bug stin shared memory. Otan epilegetai na dimiourgi8ei pli8os salatwn
>100 h timi pou pernietai stin shared memory ginetai arnitiki kai den exw entopisei ton logo.

I ka8e diergasia exei ton prwsopiko tis xrono kai roloi ektelesis. Telos to xroniko peri8wrio 
ektelesis twn saladmaker den exei ulopoih8ei. Diladi oi saladmaker ektelountai mexri na teleiwsoun
oi salates.

Ola ta upoloipa zitoumena kai ektupwseis tis askisis exoun ulopoih8ei.