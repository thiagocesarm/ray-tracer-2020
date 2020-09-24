#ifndef BUFFER_H
#define BUFFER_H

#include <memory>  // unique_ptr<>
#include <cstring> // memset, memcpy
#include <exception> // std::invalid_argument
#include <iostream> // operator<<

namespace rt3 {

    //! Represents a buffer (matrix) of information.
    /*!
     * A buffer might be use to store color (color buffer), or depth (depth buffer) for instance.
     * We define a buffer by specifying width, height and depth for each component.
     * A buffer is just a long array, treated as a matrix.
     * \tparam T Buffer data type.
     */
    template < typename T = unsigned char >
    class Buffer
    {
        private:

            /// Allocates the buffer's data memory.
            std::unique_ptr< T[] >  allocate( void )
            {
                return std::move( std::make_unique< T[] > (m_w * m_h * m_d) );
            }

            /// Returns the buffer data offset based on the provided coordinates.
            size_t offset( const size_t& r, const size_t& c, const size_t& d ) const
            { return ( r*m_w*m_d*sizeof(T) + c*m_d*sizeof(T) + d*sizeof(T) ); }

        public:

            //=== Special members
            /// Constructor
            /*! Creates an empty buffer of the requested size.
             * @param w_ The buffer width (in pixels).
             * @param h_ The buffer height (in pixels).
             */
            Buffer( size_t w=0, size_t h=0, size_t d=1 ) :
                m_w{w}, m_h{h}, m_d{d}
            {
                m_data = allocate();
                clear();
                //std::cout << ">>> [Buffer] allocated " << m_w << "," << m_h << ","<< m_d << " size " << sizeof(T) << std::endl;
            }

            /// Destructor.
            virtual ~Buffer( void )
            {
                // Do nothing, RAII (resource acquisition is resource initialization) approach
            }

            //=== Special members
            /// Copy constructor.
            Buffer( const Buffer& clone )
            {
                std::cout << "Buffer::copy constructor\n";
                // Copy the clone's info.
                m_w = clone.m_w;
                m_h = clone.m_h;
                // create new memory
                //m_data.reset( allocate() );
                m_data = allocate();
                // Copy data from clone.
                memcpy( m_data.get(), clone.m_data.get(), clone.size() );
            }
            /// Assignment operator.
            Buffer & operator=( const Buffer& clone )
            {
                std::cout << "Buffer::operaror=\n";
                if ( this != &clone  )
                {
                    // Copy clone's information.
                    m_w= clone.m_w;
                    m_h= clone.m_h;
                    // release old memory and at the same time create a new memory
                    //m_data.reset( allocate() );
                    m_data = allocate();
                    // Copy pixels from clone.
                    memcpy( m_data.get(), clone.m_data.get(), clone.size() );
                }

                return *this;
            }

            /// Move constructor.
            Buffer( Buffer&& rvalue )
            {
                std::cout << "Buffer::Move constructor\n";
                // Steal the rvalue's resources.
                m_w= rvalue.m_w;
                m_h= rvalue.m_h;
                m_data.reset( rvalue.m_data.release() );
                // Set rvalue to a initial null state.
                rvalue.m_data.reset(nullptr);
                rvalue.m_w= 0;
                rvalue.m_h= 0;
            }
            /// Move assignment operator.
            Buffer & operator=( Buffer&& rvalue )
            {
                std::cout << "Buffer::operator= Move\n";
                // Steal the rvalue's values.
                m_w= rvalue.m_w;
                m_h= rvalue.m_h;
                m_data.reset( rvalue.m_data.release() );
                // Set clone to a initial null state.
                rvalue.m_data.reset(nullptr);
                rvalue.m_w= 0;
                rvalue.m_h= 0;

                return *this;
            }

            //=== Members
            /// Clear the buffer with the background color.
            void clear( void )
            {
                // set all data to zero.
                std::memset( m_data.get(), 0, this->size() );
            }

            /// Assign a `value` to all locations of the buffer.
            void assign( const T& value )
            {
                // set all data to zero.
                std::memset( m_data.get(), value, this->size() );
            }

            /// Assigns `value` to the buffer at location `(row,col)`.
            void set( const size_t& row, const size_t& col, const size_t& depth, const T& value )
            {
                if ( row > m_h or col > m_w or depth > m_d )
                    throw std::invalid_argument( "Buffer::set(row,col,depth): Invalid data coordinates!" );
                //std::memcpy( m_data.get()+offset(row,col,depth), &value, sizeof(T) );
                m_data[ offset(row,col,depth) ] = value;
            }
            /// Enables syntax like: color_buffer( row, col ) = color24(255,0,0);
            T& operator()( const size_t& row, const size_t& col, const size_t& depth=0 )
            { return m_data[ offset(row,col,depth) ]; }

            /// Retrieves a value from the buffer at the `(row,col)` location.
            T get( const size_t& row, const size_t& col, const size_t& depth=0 ) const
            {
                std::cout << ">>> [Buffer::get()] (" << row << "," << col << ")\n";
                std::cout << "    data = " << m_data << ", offset " << offset(row,col, depth) << std::endl;
                if ( row > m_h or col > m_w or depth > m_d )
                    throw std::invalid_argument( "Buffer::get(row,col,depth): Invalid data coordinates!" );
                return m_data[ offset(row,col,depth) ];
            }
            /// Enables syntax like: color24 background = color_buffer( row, col );
            const T& operator()( const size_t& row, const size_t& col, const size_t& depth=0 ) const
            { return m_data[ offset(row,col,depth ) ]; }

            //=== Attribute accessors members.
            /// Get the buffer width.
            size_t width( void ) const
            { return m_w; }
            /// Get the buffer height.
            size_t height( void ) const
            { return m_h; }
            /// Get the buffer depth.
            size_t depth( void ) const
            { return m_d; }
            /// Return a raw pointer to the entire buffer.
            T* raw_data( void ) const
            { return m_data.get(); }
            /// Returns the buffer size in bytes.
            size_t size(void) const
            { return m_w * m_h * m_d * sizeof(T); }


            //=== Data members.
        private:
            size_t m_w; //!< The buffer width.
            size_t m_h; //!< The buffer height.
            size_t m_d; //!< The buffer depth.
            std::unique_ptr< T[] > m_data; //!< The buffer data, stored as a matrix of depth components.
    };
} // namespace

    /// Prints out the buffer.
    template < typename T >
        std::ostream& operator<<( std::ostream& os, const rt3::Buffer<T>& b )
        {
            for ( auto r{0u} ; r < b.height() ; r++ )
            {
                for ( auto c{0u} ; c < b.width() ; c++ )
                {
                    os << "( ";
                    for ( auto d{0u} ; d < b.depth(); d++ )
                    {
                        auto value = b( r, c, d );
                        os << int(value) << " ";
                    }
                    os << ")";
                }
                os << std::endl;
            }
            return os;
        }

#endif // BUFFER_H
