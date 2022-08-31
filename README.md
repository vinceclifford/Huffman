# Huffman

This is an implmentation of Huffmans-Enkoding. The Kompression of an arbitrary file is done losslessly through prefix codes. Any file format can be compressed through this implementation. A compressed file will be stored in a so-called Huffman-File (.huff) and can be decoded with this program. There are a staggering amount of minute optimization to ensure optimal runtime and maximal kompression ratio. 

# Compilation

Before compilation the code has to be cloned. Run the command 
````
git clone https://github.com/vinceclifford/Huffman.git
````
to clone the repo onto your local machine. 

Once the code is cloned, it can be compiled. Due to the complexity of this project I simplified the compiling and building process with a MAKEFILE. To compile and link the program run the command: 

````
make 
````
This should take care of the entire process and result in a single executable file called "huffman"

# General Usage

One can run the program as follows:
````
./huffman [Options] [Input] [Output]
````
There are following options to run the program: 

``-B<int>`` This option run the compression / decompression int many times and log the runtime. Default when set B1
`-o` With this flag the output file can be specified
`-b<int>`, `--batchsize<int>` 


