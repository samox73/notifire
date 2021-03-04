#include <xpp/xpp.hpp>

using Connection = xpp::connection<>;
using Registry = xpp::event::registry<Connection &>;
using Window = xpp::window<Connection &>;
using XcbWindow = xpp::window<xcb_connection_t *>;

int main(int argc, char *argv[]) {
    Connection connection{};
    Registry registry{connection};

    // Print out all available font paths
    auto && paths = connection.get_font_path().path();
    std::cout << "paths "
              << "(length: " << std::distance(paths.begin(), paths.end()) << "):"
              << std::endl;
    for (auto && path : paths) {
        std::cout << "path [" << path.length() << "]: " << path << std::endl;
    }
    std::cout << std::endl;

    // Print out all available fonts
    auto && fonts = connection.list_fonts(8, 1, "*").names();
    std::cout << "fonts "
              << "(length: " << std::distance(fonts.begin(), fonts.end()) << "):"
              << std::endl;
    for (auto && name : fonts) {
        std::cout << "font [" << name.length() << "]: " << name << std::endl;
    }
    std::cout << std::endl;

    // Print all windows and their subwindows
    auto tree = connection.root<Window>().query_tree();
    std::cout << "children: " << std::endl;
    for (auto && child : tree.children<XcbWindow>()) {
        std::cout << child << " ";
        auto siblings = child.query_tree().children();
        auto siblings_length = std::distance(siblings.begin(), siblings.end());
        if (siblings_length > 0) {
            std::cout << std::hex << "[" << siblings_length
                      << " sibling" << (siblings_length > 1 ? "s" : "") << ": ";
            for (auto && sibling : siblings) {
                std::cout << "0x" << sibling << (--siblings_length > 0 ? ", " : "");
            }
            std::cout << std::dec << "]" << std::endl;
        } else {
            std::cout << "[no siblings]" << std::endl;
        }
    }
    std::cout << std::endl;

    // Creates an atom called "XPP_STRING_PROPERTY_DEMO" with a string property
    // "xpp is working" on the root window
    // check with `xprop -root XPP_STRING_PROPERTY_DEMO`
    try {
        auto my_string_atom =
            xpp::x::intern_atom(connection, false, "XPP_STRING_PROPERTY_DEMO");

        std::string my_string("xpp is working!");

        std::cout << "atom for \"XPP_STRING_PROPERTY_DEMO\": "
                  << my_string_atom.atom() << std::endl;

        auto atom_name = connection.get_atom_name(my_string_atom.atom());
        std::cout << "atom name: " << atom_name.name() << std::endl;;

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

    return EXIT_SUCCESS;
}