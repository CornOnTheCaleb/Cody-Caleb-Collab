#ifndef IMAGE_H
#define IMAGE_H

class Image
{
  private:
    // Pure RGB pixel data from top left to bottom right (red, green, blue)
    unsigned char * m_pixelData;

    // Width of image
    int m_width;

    // Height of image
    int m_height;

    // Channels of the image
    int m_channels;

    // Image has been resized
    bool m_resized;
    
    // Check if valid row and column
    bool is_valid_position (const int column, const int row) const;

  private:
    // Clears everything up
    void clear ();

  public:
    // Default constructor
    Image ();

    // Constructor with width and height
    Image (const int width, const int height, const int channels);

    // Copy constructor
    Image (const Image & image);

    // Operator=
    Image & operator= (const Image & image);

    // Destructor
    ~Image ();

    // Load data from image file
    void load_from_file (const char * filename);

    // Save data to image file
    void save_to_file (const char * filename);

    // Resize image to new dimensions
    void resize (const int width, const int height);

    // Get width of image
    int get_width () const;

    // Get height of image
    int get_height () const;

    // Get channels of image
    int get_channels () const;

    // Get color values of a particular pixel, return whether successful
    bool get_pixel (const int column, const int row, unsigned char & red, unsigned char & green, unsigned char & blue) const;

    // Set color values of a particular pixel, return whether successful
    bool set_pixel (const int column, const int row, const unsigned char red, const unsigned char green, const unsigned char blue);

};

#endif
