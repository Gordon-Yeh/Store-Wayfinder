## Convert .sof file to .jic
1. in Quartus go to `File > Convert Programing Files...`
2. select `JTAG Indirect Configuration File (.jic)` for *Programming file type*
3. Choose `EPCS128` from the *Configuration device field*
4. Choose `Active Serial` from the *Mode filed*
5. Browse to the target directory from the File name field and specify the name of output file
6. Click on the `SOF data` in the section of *Input files to convert*
7. Click *Add File*
8. Select the `.sof` to be converted to a `.jic` file from the Open File dialog.
9. Click *Open*
10. Click on the `Flash Loader` and click `Add Device`
11. Find and check `Cyclone V` and `5CSEMA5` and press *OK*
12. Click `Generate`

## Altera Embedded Command Shell
download preloader (for windows):  
`C:/Altera/15.0/quartus/bin64/quartus_hps --cable="DE-SoC [USB-1]" -o GDBSERVER --gdbport0=3335 --preloader=C:/Altera/15.0/University_Program/Monitor_Program/arm_tools/u-boot-spl.srec --preloaderaddr=0xffff1398`
