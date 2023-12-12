#include <iostream>
#include <string>
/**
 * Proxy classes.
*/

/**
 * Some of the concept in this content is either outdated or being implemented into the C++ Standard.
 *
 * While the Proxy pattern isn’t a frequent guest in most C++ applications, it’s still very handy in some special cases.
 * It’s irreplaceable when you want to add some additional behaviors to an object of some existing class without
 * changing the client code.
*/

/**
 * A proxy class is a type of class that acts as an intermediary or a 'stand-in' for another class or resource.
 * It is used when direct access to the original class is not ideal or possible due to various reasons such as
 * performance considerations, memory management, additional functionality, or access control.
*/

/**
 * Concept: Imagine you're writing a software application, and you need to handle a complex object.
 * This object is expensive to create and manage, so you want to optimize how you use it. Instead of working with the
 * object directly, you use a proxy class. This proxy class looks and behaves like your complex object, but internally,
 * it manages the creation, life cycle, and access to the actual object in a more efficient way.
 *
 * In this example, ImageProxy acts as a proxy to LargeImage. When you create an instance of ImageProxy, it doesn't
 * load the image immediately. The image is only loaded when you call the display method. This can save resources if,
 * for instance, the image is never displayed.
 *
 *
 * Key Points:
 *
 * Lazy Initialization: The real object (LargeImage) is not created until it's actually needed.
 * Resource Management: The proxy can manage the resource (like memory for LargeImage) more efficiently.
 * Controlled Access: The proxy controls how and when the client accesses the underlying resource.
*/
// Imagine this as a large image resource.
class LargeImage
{
    public:
        LargeImage(const std::string& filename)
        {
            // Expensive operation to load an image from a file.
            std::cout << "Loading image from " << filename << std::endl;
        }

        void display()
        {
            std::cout << "Displaying image." << std::endl;
        }
};


// Proxy class for the LargeImage.
class ImageProxy
{
    private:
        std::string filename;
        LargeImage* image;


    public:
        ImageProxy(const std::string& filename) : filename(filename), image(nullptr) {}

        ~ImageProxy()
        {
            delete image;
        }

        void display()
        {
            // Lazy initialization: LargeImage is created only when actually needed.
            if (!image) {
                image = new LargeImage(filename);
            }
            image->display();
        }
};


int main() {
    ImageProxy proxy("sample.jpg");

    // At this point, the image is not loaded yet.
    std::cout << "Image proxy created." << std::endl;

    // Image is loaded and displayed only when this method is called.
    proxy.display();

    return 0;
}


/**
 * Limitations and Challenges of Proxy Classes:
 * While proxy classes offer a solution, they introduce their own set of complexities and limitations. Proxy objects do
 * not always seamlessly replace real objects. For instance, addressing (&) proxy objects behaves differently than real
 * objects, and certain operations (like +=, *=, etc.) may not work as expected with proxies.
 *
 *
 * Overall Assessment:
 * Despite their limitations, proxy classes can be a powerful tool in C++ for implementing features not natively
 * supported by the language, such as multidimensional arrays and distinguishing read/write operations in overloaded
 * operators. However, their use adds complexity and can change the semantics of a class, making system design and
 * maintenance more challenging.
*/





