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

The output of the usage example from the main file is shown below:

```
ADDR: 0x602000000070, NUM : 7230746117032715333, VAL : d;
ADDR: 0x6020000000f0, NUM : 5887555801836278008, VAL : h;
ADDR: 0x602000000010, NUM : 5476925749827261289, VAL : a;
ADDR: 0x602000000110, NUM : 2961502581317252253, VAL : i;
ADDR: 0x6020000000b0, NUM : 1940165376255661072, VAL : f;
ADDR: 0x602000000050, NUM : 1784957980908272815, VAL : c;
ADDR: 0x602000000090, NUM : 1277728417939753984, VAL : e;
ADDR: 0x602000000030, NUM : 1241716904600769112, VAL : b;
ADDR: 0x602000000130, NUM : 1080230712925847358, VAL : j;
ADDR: 0x6020000000d0, NUM : 773675782253554260, VAL : g;
ADDR: 0x602000000150, NUM : 123, VAL : z;

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

Dump Time: Wed Jan 24 01:21:01 2024

Tree[0x608000000020] tree called from int main() in main.cpp(80)
	{
		 nodes              = 0x603000000040
		 number_of_nodes    = 11
		 containerCtor      = 0x55a6b9af1d55
		 containerDtor      = 0x55a6b9af1d91
		 containerCopy      = 0x55a6b9af1db0
		 containerComp      = 0x55a6b9af1f89
		 containerPrint     = 0x55a6b9af20ec
		 CREATION_FILE[0x55a6b9afc360] = main.cpp
		 CREATION_FUNC[0x55a6b9afc3e0] = int main()
		 CREATION_LINE[0x608000000070] = 45
	}
Error list:
	{
	}

				 Left [0x603000000070]
				/
Node[0x603000000040] ————————— | 
				\
				 Right[0x6030000000d0]


				 Left [0x603000000160]
				/
Node[0x603000000070] ————————— | 
				\
				 Right[0x6030000000a0]


				 Left [0x603000000220]
				/
Node[0x603000000160] ————————— | 
				\
				 Right[0x6030000001f0]


Node[0x603000000220] ————————— | 


Node[0x6030000001f0] ————————— | 


				 Left [0x603000000100]
				/
Node[0x6030000000a0] ————————— | 
				\
				 Right[0x603000000130]


Node[0x603000000100] ————————— | 


Node[0x603000000130] ————————— | 
				\
				 Right[0x6030000001c0]


Node[0x6030000001c0] ————————— | 


				 Left [0x603000000190]
				/
Node[0x6030000000d0] ————————— | 


Node[0x603000000190] ————————— | 

MIN NODE:ADDR: 0x602000000150, NUM : 123, VAL : z;
MAX NODE:ADDR: 0x602000000070, NUM : 7230746117032715333, VAL : d;
FOUND NODE:ADDR: 0x602000000150, NUM : 123, VAL : z;
ADDR: 0x602000000070, NUM : 7230746117032715333, VAL : d;
ADDR: 0x6020000000f0, NUM : 5887555801836278008, VAL : h;
ADDR: 0x602000000010, NUM : 5476925749827261289, VAL : a;
ADDR: 0x602000000110, NUM : 2961502581317252253, VAL : i;
ADDR: 0x6020000000b0, NUM : 1940165376255661072, VAL : f;
ADDR: 0x602000000050, NUM : 1784957980908272815, VAL : c;
ADDR: 0x602000000090, NUM : 1277728417939753984, VAL : e;
ADDR: 0x602000000030, NUM : 1241716904600769112, VAL : b;
ADDR: 0x602000000130, NUM : 1080230712925847358, VAL : j;
ADDR: 0x6020000000d0, NUM : 773675782253554260, VAL : g;
NEW MIN NODE:ADDR: 0x6020000000d0, NUM : 773675782253554260, VAL : g;
NEW MAX NODE:ADDR: 0x602000000070, NUM : 7230746117032715333, VAL : d;
An example of the output of a pair:
				 Left [0x603000000070]
				/
Node[0x603000000040] ————————— | 
				\
				 Right[0x6030000000d0]

```