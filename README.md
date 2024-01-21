# Universal-Binary-Tree 

The program is an implementation of a binary tree, but any object can be used as its elements. The code is mostly optimized for C, C++ is used for better optimization.

## Install
Just make
```bash
make
```
## Start
Just start
```bash
./besttree
```

## Example

Main provides a simple example (a bijection of two numbers in one with a char value), this is approximately the output (P.S. the output format is in reverse order, therefore descending):

```
NUM:8049723784985636131 VAL:h 
NUM:5767527691793209193 VAL:b 
NUM:4221150983251989987 VAL:i 
NUM:3514484459550757201 VAL:a 
NUM:2836928958607447591 VAL:c 
NUM:2821957166114599882 VAL:f 
NUM:2807610796395778873 VAL:d 
NUM:1778288188847856934 VAL:g 
NUM:1595180327595782906 VAL:e 
NUM:1292100317725592422 VAL:j 

┳┓┳┳┳┳┓┏┓          .-‾‾‾‾‾‾‾‾-.
┃┃┃┃┃┃┃┃┃         /            \
┻┛┗┛┛ ┗┣┛        |,  .-.  .-.  ,|
                 | )(_ /  \ _)( |
                 |/     /\     \|
       (@_       <_     ^^     _>
  _     ) \_______\__|IIIIII|__/__________________________
 (_)@8@8{}<_______________________________________________\
        )_/        \  IIIIII  /
       (@           ‾‾‾‾‾‾‾‾‾‾

Tree[0x608000000020] tree called from int main() in main.cpp(40)
	{
		 nodes              = 0x603000000040
		 number_of_nodes    = 10
		 containerCtor      = 0x55ef66b58661
		 containerDtor      = 0x55ef66b5869d
		 containerCopy      = 0x55ef66b586bc
		 containerComp      = 0x55ef66b58895
		 containerPrint     = 0x55ef66b589f8
		 CREATION_FILE[0x55ef66b5f380] = main.cpp
		 CREATION_FUNC[0x55ef66b5f3c0] = int main()
		 CREATION_LINE[0x608000000070] = 20
	}
Error list:
	{
	}

				 Left [0x6030000000a0]
				/
Node[0x603000000040] ————————— | 
				\
				 Right[0x603000000070]


				 Left [0x6030000000d0]
				/
Node[0x6030000000a0] ————————— | 


				 Left [0x603000000100]
				/
Node[0x6030000000d0] ————————— | 
				\
				 Right[0x603000000130]


				 Left [0x6030000001f0]
				/
Node[0x603000000100] ————————— | 
				\
				 Right[0x603000000160]


Node[0x6030000001f0] ————————— | 


Node[0x603000000160] ————————— | 


Node[0x603000000130] ————————— | 


				 Left [0x6030000001c0]
				/
Node[0x603000000070] ————————— | 
				\
				 Right[0x603000000190]


Node[0x6030000001c0] ————————— | 


Node[0x603000000190] ————————— | 


```