/* Contains info. about type, size, and layout of file */
typedef struct _BITMAPFILEHEADER
{
    unsigned short bfType;           // Magic number; must be 0x4D42
    unsigned int   bfSize;           // The size of file in bytes
    unsigned short bfReserved1;      // Reserved; must be zero
    unsigned short bfReserved2;      // Reserved; must be zero
    unsigned int   bfOffBits;        // The offset from the beginning of 
                                     // the BITMAPFILEHEADER structure
} __attribute__((packed)) BITMAPFILEHEADER;

/* Contains info. about dim. & color format */
typedef struct _BITMAPINFOHEADER 
{
    unsigned int   biSize;           // The number of bytes required by structure
    int            biWidth;          // Width of bitmap, in pixels
    int            biHeight;         // Height of bitmap, in pixels
    unsigned short biPlanes;         // Num. of planes; must be set to 1
    unsigned short biBitCount;       // The number of bits-per-pixel
    unsigned int   biCompression;    // Type of compression
    unsigned int   biSizeImage;      // The size of image in bytes
    int            biXPelsPerMeter;  // Horizontal resolution in pixels-per-meter
    int            biYPelsPerMeter;  // Vertical resolution in pixels-per-meter
    unsigned int   biClrUsed;        // Num. of color indexes that are actually used
    unsigned int   biClrImportant;   // Num. of color indexes that are required
} __attribute__((packed)) BITMAPINFOHEADER;

/* Describes a color w/ RGB */
typedef struct _RGBTRIPLE
{
    unsigned char rgbtBlue;
    unsigned char rgbtGreen;
    unsigned char rgbtRed;
} __attribute__((packed)) RGBTRIPLE;
