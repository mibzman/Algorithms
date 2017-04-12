# Seam Carve Image

This program takes an image an removes "seams" that have a lower "energy" compared to the surrounding pixels.

For simplicity, this program operates only on .pgm files. 

input: ./ImageCarver \<imageName\>.pgm \<VerticalSeams\> \<HorizontalSeams\>
output: \<imageName\>_processed.pgm

## This program operates as followes:

### For vertical seams:

- Parse image into martix
- Compute the energy of each pixel by summing the absolute value of the difference between all surrounding pixels
- Start at the bottom an work up, adding the energy of the minimum proceeding neighbor to the current 'cumulative energy'
- Find the lowest cumulative energy on the bottom, and work up, marking the smallest contiguous set of cumulative energy
- Remove marked pixels

### For horizontal seams:

- Transpose Image
- Follow procedure for vertical seams
- Transpose Image
