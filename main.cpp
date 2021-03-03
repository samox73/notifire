//// This demo will allow the user to click on a window, grab the keyboard on it
//// and then print every key press and release event. Will exit when Escape is
//// pressed
//
//#include <iostream>
//
//#include <X11/Xlib.h> // XKeysymToString
//#include <X11/keysym.h> // XK_Escape
//#include <X11/cursorfont.h> // XC_cross
//#include <xpp/xpp.hpp>
//
//// global variable to indicate whether the event loop should exit
//bool g_quit = false;
//
//// typedefs for convenience
//namespace x {
//    typedef xpp::connection<> connection;
//    typedef xpp::event::registry<connection &> registry;
//
//    typedef xpp::font<connection &> font;
//    typedef xpp::cursor<connection &> cursor;
//    typedef xpp::window<connection &> window;
//
//    typedef xpp::x::event::key_press<connection &> key_press;
//    typedef xpp::x::event::key_release<connection &> key_release;
//    typedef xpp::x::event::button_press<connection &> button_press;
//};
//
//// The event handler class
//// Implements the xpp::event::sink<..> interface with all events we are
//// interested in as template parameters
//template<typename Connection>
//class key_printer
//    : public xpp::event::sink<x::key_press, x::key_release, x::button_press>
//{
//public:
//    template<typename C>
//    key_printer(C && c)
//        : m_c(std::forward<C>(c))
//    {}
//
//    // xpp::event::sink<x::key_press>::handle(...) interface
//    void handle(const x::key_press & e)
//    {
//        auto kbd_mapping = m_c.get_keyboard_mapping(e->detail, 1);
//        // take the first value from the kbd_mapping list
//        // This might throw, but for simplicity, no error handling here
//        auto keysym = *kbd_mapping.keysyms().begin();
//
//        if (keysym == XK_Escape) {
//            std::cerr << "quitting" << std::endl;
//            // parameter has a default value: XCB_TIME_CURRENT_TIME
//            m_c.ungrab_keyboard();
//            g_quit = true;
//        } else {
//            std::cerr << "key press: " << XKeysymToString(keysym) << std::endl;
//        }
//    }
//
//    // xpp::event::sink<x::key_release>::handle(...) interface
//    void handle(const x::key_release & e)
//    {
//        auto kbd_mapping = m_c.get_keyboard_mapping(e->detail, 1);
//        auto keysym = *kbd_mapping.keysyms().begin();
//        std::cerr << "key release: " << XKeysymToString(keysym) << std::endl;
//    }
//
//    // xpp::event::sink<x::button_press>::handle(...) interface
//    void handle(const x::button_press & e)
//    {
//        m_c.ungrab_pointer(XCB_TIME_CURRENT_TIME);
//
//        // event & reply accessors have a default template parameter, the c-type
//        // Usable with any type which is constructible from the c-type or
//        // connection + c-type
//        // xcb_window_t grab_window = e.event();
//        x::window grab_window = e.event<x::window>();
//
//        if (e->event == e->root) {
//            // xpp::window, etc. are assignable with the c-type
//            grab_window = e.child();
//            // xpp::window, etc. are implicitly convertible to c-type
//            auto translate = grab_window.translate_coordinates(grab_window, 1, 1);
//            grab_window = translate->child;
//        }
//
//        *m_c.grab_keyboard(true, grab_window,
//                           XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
//
//        std::cerr << "Grabbed " << grab_window
//                  << ". Press Escape to quit." << std::endl;
//    }
//
//private:
//    Connection m_c;
//};
//
//int main(int, char **)
//{
//    try {
//        // xpp::connection is implicitly convertible to xcb_connection_t *
//        // Hence, it can be used with all xcb_* c functions.
//        // However, this is not demonstrated here.
//        x::connection connection;
//        x::registry registry(connection);
//
//        key_printer<x::connection &> key_printer(connection);
//        registry.attach(0, &key_printer);
//
//        x::font font = x::font::open_checked(connection, "cursor");
//
//        // x::font, etc. is implicitly convertible to xcb_font_t
//        x::cursor cursor = x::cursor::create_glyph_checked(connection, font, font,
//                                                           XC_cross, XC_cross + 1, 0, 0, 0, 0xffff, 0xffff, 0xffff);
//
//        *connection.grab_pointer(false, connection.root(),
//                                 XCB_EVENT_MASK_BUTTON_PRESS,
//                                 XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC,
//                                 XCB_NONE, cursor);
//        // default value for time = XCB_TIME_CURRENT_TIME);
//
//        std::cerr << "Please click on a window" << std::endl;
//
//        while (! g_quit) {
//            connection.flush();
//            registry.dispatch(connection.wait_for_event());
//        }
//
//    } catch (const std::exception & error) {
//        std::cerr << "Exception (std::exception) in "
//                  << __FILE__ << " @ line " << __LINE__ << ", what(): "
//                  << error.what() << std::endl;
//        std::exit(EXIT_FAILURE);
//    }
//
//    return EXIT_SUCCESS;
//}


#include <iostream>

#include "xpp/xpp.hpp"
#include "xpp/proto/randr.hpp"
#include "xpp/proto/damage.hpp"
#include "xpp/proto/render.hpp"

// typedefs for convenience
namespace x {
    typedef xpp::connection<xpp::randr::extension,
        xpp::damage::extension,
        xpp::render::extension>
        connection;

    typedef xpp::event::registry<connection &,
        xpp::randr::extension,
        xpp::damage::extension,
        xpp::render::extension>
        registry;

    typedef xpp::font<connection &> font;
    typedef xpp::cursor<connection &> cursor;
    typedef xpp::window<connection &> window;
    typedef xpp::window<xcb_connection_t *> xcb_window;
};

int main(int, char **)
{
    x::connection connection;
    x::registry registry(connection);

    // Print out all available font paths
    auto && paths = connection.get_font_path().path();
    std::cerr << "paths "
              << "(length: " << std::distance(paths.begin(), paths.end()) << "):"
              << std::endl;
    for (auto && path : paths) {
        std::cerr << "path [" << path.length() << "]: " << path << std::endl;
    }
    std::cerr << std::endl;

    // Print out all available fonts
    auto && fonts = connection.list_fonts(8, 1, "*").names();
    std::cerr << "fonts "
              << "(length: " << std::distance(fonts.begin(), fonts.end()) << "):"
              << std::endl;
    for (auto && name : fonts) {
        std::cerr << "font [" << name.length() << "]: " << name << std::endl;
    }
    std::cerr << std::endl;

    // Print all windows and their subwindows
    auto tree = connection.root<x::window>().query_tree();
    std::cerr << "children: " << std::endl;
    for (auto && child : tree.children<x::xcb_window>()) {
        std::cerr << child << " ";
        auto siblings = child.query_tree().children();
        auto siblings_length = std::distance(siblings.begin(), siblings.end());
        if (siblings_length > 0) {
            std::cerr << std::hex << "[" << siblings_length
                      << " sibling" << (siblings_length > 1 ? "s" : "") << ": ";
            for (auto && sibling : siblings) {
                std::cerr << "0x" << sibling << (--siblings_length > 0 ? ", " : "");
            }
            std::cerr << std::dec << "]" << std::endl;
        } else {
            std::cerr << "[no siblings]" << std::endl;
        }
    }
    std::cerr << std::endl;

    // Creates an atom called "XPP_STRING_PROPERTY_DEMO" with a string property
    // "xpp is working" on the root window
    // check with `xprop -root XPP_STRING_PROPERTY_DEMO`
    try {
        auto my_string_atom =
            xpp::x::intern_atom(connection, false, "XPP_STRING_PROPERTY_DEMO");

        std::string my_string("xpp is working!");

        std::cerr << "atom for \"XPP_STRING_PROPERTY_DEMO\": "
                  << my_string_atom.atom() << std::endl;

        auto atom_name = connection.get_atom_name(my_string_atom.atom());
        std::cerr << "atom name: " << atom_name.name() << std::endl;;

        connection.change_property_checked(
            XCB_PROP_MODE_REPLACE, connection.root(),
            my_string_atom.atom(), XCB_ATOM_STRING, 8,
            // using Iterator begin + end here
            my_string.begin(), my_string.end());

        // this will deliberately fail because window = 0
        // However, the previous call to change_property succeeded,
        // so everything is just fine
        connection.change_property_checked( XCB_PROP_MODE_REPLACE, 0,
                                            my_string_atom.atom(), XCB_ATOM_STRING, 8,
            // using length() & c_str()
                                            my_string.length(), my_string.c_str());

    } catch (const std::exception & e) {
        std::cerr << "change property failed: " << e.what() << std::endl;
    }
    std::cerr << std::endl;

    // Get the _NET_CLIENT_LIST_STACKING property
    // If an error occurs, it will be thrown only when trying to access the reply
    std::string _net_client_list_stacking = "_NET_CLIENT_LIST_STACKING";
    auto net_client_list_stacking_atom =
        connection.intern_atom(false, _net_client_list_stacking);
    auto net_client_list_stacking = connection.get_property(
        false, connection.root(), net_client_list_stacking_atom.atom(),
        XCB_ATOM_WINDOW, 0, UINT32_MAX);

    try {
        std::cerr << _net_client_list_stacking << " (xcb_window_t):" << std::hex;
        for (auto && w : net_client_list_stacking.value<xcb_window_t>()) {
            std::cerr << " 0x" << w;
        }
        std::cerr << std::dec << std::endl;

        std::cerr << _net_client_list_stacking << " (x::window):";
        for (auto && w : net_client_list_stacking.value<x::window>()) {
            std::cerr << " " << w;
        }
        std::cerr << std::endl;

        std::cerr << _net_client_list_stacking << " (x::xcb_window):";
        for (auto && w : net_client_list_stacking.value<x::xcb_window>()) {
            std::cerr << " " << w;
        }
        std::cerr << std::endl;

    } catch (const std::exception & e) {
        std::cerr << "Could not get " << _net_client_list_stacking << " property: "
                  << e.what() << std::endl;
    }
    std::cerr << std::endl;

    // Randr needs query_version to work properly in subsequent calls
    // If methods are ambiguous (like query_version, then the extension interface
    // can be accessed through "extension_name()" (e.g. randr() or damage())
    connection.randr().query_version(XCB_RANDR_MAJOR_VERSION,
                                     XCB_RANDR_MINOR_VERSION);

    connection.select_input_checked(connection.root(), XCB_RANDR_NOTIFY);

    const auto & randr_ext = connection.extension<xpp::randr::extension>();

    std::cerr << "RandR Extension" << std::endl;
    std::cerr << "\tfirst_event: " << (int)randr_ext->first_event << std::endl;
    std::cerr << "\tfirst_error: " << (int)randr_ext->first_error << std::endl;

    const auto & damage_ext = connection.extension<xpp::damage::extension>();

    std::cerr << "Damage Extension" << std::endl;
    std::cerr << "\tfirst_event: " << (int)damage_ext->first_event << std::endl;
    std::cerr << "\tfirst_error: " << (int)damage_ext->first_error << std::endl;

    std::cerr << std::endl;

    try {
        // Produces XCB_RANDR_BAD_OUTPUT error
        auto output_info = connection.get_output_info(-1);
        output_info.get();
    } catch (const std::exception & e) {
        std::cerr << "get_output_info error: " << e.what() << std::endl;
    }

    try {
        // Produces XCB_RANDR_BAD_CRTC error
        auto crtc_info = connection.get_crtc_info(-1);
        crtc_info.get();
    } catch (const std::exception & e) {
        std::cerr << "get_crtc_info error: " << e.what() << std::endl;
    }

    // Produces XCB_RANDR_BAD_OUTPUT error in event queue
    auto output_info = connection.get_output_info_unchecked(-1);
    output_info.get();

    // Produces XCB_RANDR_BAD_CRTC error in event queue
    auto crtc_info = connection.get_crtc_info_unchecked(-1);
    crtc_info.get();

    try {
        // XCB_VALUE error
        connection.change_output_property_checked(-1, -1, -1, 0, 0, 0, nullptr);
    } catch (const std::exception & e) {
        std::cerr << "change_output_property error: " << e.what() << std::endl;
    }

    // XCB_VALUE error in event queue
    connection.change_output_property(-1, -1, -1, 0, 0, 0, nullptr);

    try {
        // XCB_RENDER_PICT_FORMAT error
        auto pict_index_values = connection.query_pict_index_values(-1);
        pict_index_values.get();
    } catch (const std::exception & e) {
        std::cerr << "query_pict_index_values error: " << e.what() << std::endl;
    }

    try {
        // XCB_RENDER_PICTURE error
        connection.change_picture_checked(-1, 0, nullptr);
    } catch (const std::exception & e) {
        std::cerr << "change_picture error: " << e.what() << std::endl;
    }

    // XCB_RENDER_PICT_FORMAT error in event queue
    auto pict_index_values = connection.query_pict_index_values_unchecked(-1);
    pict_index_values.get();

    // XCB_RENDER_PICTURE error in event queue
    connection.change_picture(-1, 0, nullptr);

    // Poll the event queue a couple of times to get the errors
    for (int i = 0; i < 5; ++i) {
        connection.flush();
        try {
            registry.dispatch(connection.wait_for_event());
        } catch (const std::exception & e) {
            std::cerr << "std::exception in event queue: " << e.what() << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
