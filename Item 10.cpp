#include <memory>
#include <string>
#include <string_view>
#include <vector>
/**
 * Prevent resource leak in constructors.
*/

/**
 * Consider the below code.
 *
 * An exception might arise because operator new is unable to allocate enough memory for an AudioClip object.
 * One might also arise because the AudioClip constructor itself throws an exception. Regardless of the cause
 * of the exception, if one is thrown within the BookEntry constructor, it will be propagated to the site where the
 * BookEntry object is being created. If an exception is thrown during creation of the object theAudioClip is supposed
 * to point to, BookEntry’s destructor will never be called. C++ destroys only fully constructed objects, and an object
 * isn’t fully constructed until its constructor has run to completion.
*/
class Image
{
    public:
        Image(std::string_view imageData);
};

class AudioClip
{
    public:
        AudioClip(std::string_view audioData);
};

class PhoneNumber { };


// Yellow Book
class BookEntry
{
    public:
        BookEntry(std::string_view name, std::string_view address, std::string_view image, std::string_view audio)
            : m_name { name }, m_address { address }, m_image { nullptr }, m_audioClip { nullptr }
        {
            if (image != " '")
            {
                m_image = new Image { image };
            }

            if (audio != " ")
            {
                m_audioClip = new AudioClip { audio };
            }
        }

        ~BookEntry()
        {
            delete m_image;
            delete m_audioClip;
        }


    private:
        std::string m_name;
        std::string m_address;
        std::vector<PhoneNumber> m_phoneNumbers;
        Image* m_image;
        AudioClip* m_audioClip;
};


/**
 * Because C++ won’t clean up after objects that throw exceptions during construction, you must design your
 * constructors so that they clean up after themselves. Often, this involves simply catching all possible exceptions,
 * executing some cleanup code, then rethrowing the exception so it continues to propagate.
*/
BookEntry::BookEntry(std::string_view name, std::string_view address, std::string_view image, std::string_view audio)
    : m_name { name }, m_address { address }, m_image { nullptr }, m_audioClip { nullptr }
{
    // New try block
    try
    {
        if (image != " '")
        {
            m_image = new Image { image };
        }

        if (audio != " ")
        {
            m_audioClip = new AudioClip { audio };
        }
    }
    catch (...)                 // Catch any exception
    {
        // Perform necessary cleanup actions
        delete m_image;
        delete m_audioClip;

        // Propagate the exception
        throw;
    }
}


/**
 * Code duplication here is no more tolerable than it is anywhere else, so the best way to structure things is to
 * move the common code into a private helper function and have both the constructor and the destructor call it.
*/
class BookEntry2
{
    public:
        BookEntry2(std::string_view name, std::string_view address, std::string_view image, std::string_view audio)
            : m_name { name }, m_address { address }, m_image { nullptr }, m_audioClip { nullptr }
        {
            try
            {
                if (image != " '")
                {
                    m_image = new Image { image };
                }

                if (audio != " ")
                {
                    m_audioClip = new AudioClip { audio };
                }
            }
            catch (...)
            {
                cleanUp();
                throw;
            }
        }

        ~BookEntry2()
        {
            cleanUp();
        }


    private:
        void cleanUp()
        {
            delete m_image;
            delete m_audioClip;
        }

        std::string m_name;
        std::string m_address;
        std::vector<PhoneNumber> m_phoneNumbers;
        Image* m_image;
        AudioClip* m_audioClip;
};


/**
 * The code above is nice, but it doesn’t put the topic to rest. By using <memory> library, it's easier.
*/
class BookEntry3
{
    public:
        BookEntry3(std::string_view name, std::string_view address, std::string_view image, std::string_view audio)
            : m_name { name }, m_address { address },
              m_image { std::make_shared<Image>(image) },
              m_audioClip { std::make_shared<AudioClip>(audio) }
        { }

        ~BookEntry3() { };

    private:
        std::string m_name;
        std::string m_address;
        std::vector<PhoneNumber> m_phoneNumbers;
        std::shared_ptr<Image> m_image;
        std::shared_ptr<AudioClip> m_audioClip;
};