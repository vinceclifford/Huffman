# Huffman

This is an implementation of Huffman's-Encoding. The compression of an arbitrary file is done losslessly through prefix codes. Any file format can be compressed through this implementation. A compressed file will be stored in a so-called Huffman file (.huff) and can be decoded with this program. There is a staggering amount of minute optimization to ensure optimal runtime and maximal compression ratio. 

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
This should take care of the entire process and result in a single executable file called `huffman`

# General Usage

One can run the program as follows:
````
./huffman [Options] [Input] [Output]
````
There are following options to run the program: 

``-B<int>`` This option runs the compression / decompression int many times on the same file and logs the (average) runtime. Default: B1 <br />
`-o` With this flag the output file can be specified <br />
`-b<int>`, `--batchsize<int>` Specifies how big the `batchsize` is. In other words how many Bytes are read from memory at one time. Default set to 16384 Byte. Bigger batchsize results in less system calls and therefore improves performance drastically. <br />
`-s<string>`, `--sort<string>` With this option the sorting algorithm can be chosen to compare runtimes between the algorithms. Valid inputs: radix_binary, radix_decimal, shell. Default: shell <br />
`-v`, `--verbose` Verbose mode <br />
`-d` Decompress Huffman file. If this flag is not set then the input file will be compressed. If this flag is set then the input file will be interpreted as a Huffman file and will be decoded <br />
`-V<int>` Select specific program version. Default: V9. Different program versions are listed at the end of the README <br />
`-h`, `--help` Print help page <br />

# Example Encoding 
Let's assume there is a file called `input.txt` which should be compressed. 
```
./huffman input.txt -o foo
```
The above command would compress the input file into a file foo.huff. Options can be added to this command to see which effect different implementations have on the runtime. 

# Example Decoding 
The previously generated Huffman file `foo.huff` should be decoded. For that following command must be run: 
```
./huffman -d foo.huff -o output.txt
```
That result in a decompressed file called `output.txt` which is equivalent to the file `input.txt`

# Testing

This program was tested via system tests. These tests check for different modalities (eg. batchsize and sorting algorithm) whether the input file equals the compressed and then decompressed file. These tests can be found in the directory `Testing` and can be executed with the script tests.sh. The input data for this script is located in the directory `test_files`. Therefore anybody can execute their own individual tests and check for correctness of the program


# Versions
The different Versions of the program are: <br />
`-V1`   Radix sort binary       Batch size 1 <br />
`-V2`   Radix sort decimal      Batch size 1 <br />
`-V3`   Shell sort              Batch size 1 <br />
`-V4`   Radix sort binary       Batch size 4096 <br />
`-V5`   Radix sort decimal      Batch size 4096 <br />
`-V6`   Shell sort              Batch size 4096 <br />
`-V7`   Radix sort binary       Batch size 16384 <br />
`-V8`   Radix sort decimal      Batch size 16384 <br />
`-V9`   Shell sort              Batch size 16384 <br />
