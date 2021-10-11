# my_blockchain

how to run: \
```
make
``` 

```
./my_blockchain [BACKUP FILE] [TO SAVE FILE]
``` 

```
./my_blockchain backup.txt backup.txt
[-0]> add node 12
[-1]> add block 21 *
[-1]> add node 13
[-2]> sync
[s2]> ls -l
12: 21,
13: 21,
[s2]> quit
```

How it will be saved int ***.txt** :
```
nid
12
bid
21
nid
13
bid
21
```