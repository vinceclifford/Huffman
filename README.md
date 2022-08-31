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

``-B<int>`` This option runs the compression / decompression int many times and logs the runtime. Default: B1 <br />
`-o` With this flag the output file can be specified <br />
`-b<int>`, `--batchsize<int>` Specifies how big the "batchsize" is. In other words, how many Bytes are read at one time from memory. Default set to 16384 Byte. Bigger batchsize results in less system calls and therefore improves performance drastically. <br />
`-s<string>`, `--sort<string>` With this option the sorting algorithm can be chosen to compare runtimes between the algorithms. Valid inputs: radix_binary, radix_decimal, shell. Default: shell <br />
`-v`, `--verbose` Verbose mode <br />
`-d` Decompress Huffmanfile. If this flag is not set then input file will be compressed. If this flag is set then the input file will be interpreted as a Huffman-file <br />
`-V<int>` Select specific program version. Default: V9. Program Version listed at the end of the README <br />
`-h`, `--help` Print help page <br />




