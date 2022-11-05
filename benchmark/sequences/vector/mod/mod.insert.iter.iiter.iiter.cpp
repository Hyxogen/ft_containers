#include <benchmark.hpp>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include <string>

int main() {
        const std::string str(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Dui nunc mattis enim ut tellus elementum sagittis vitae et. Magna fringilla urna porttitor rhoncus dolor purus. Venenatis cras sed felis eget velit aliquet sagittis. Nisi quis eleifend quam adipiscing vitae proin. Risus ultricies tristique nulla aliquet enim tortor at auctor. Sit amet nisl suscipit adipiscing bibendum est ultricies. Facilisi etiam dignissim diam quis enim lobortis scelerisque fermentum. Lacinia at quis risus sed vulputate. Ut diam quam nulla porttitor. Mattis pellentesque id nibh tortor id aliquet lectus proin. Amet dictum sit amet justo donec enim. Amet consectetur adipiscing elit ut aliquam. Habitant morbi tristique senectus et netus et malesuada. Integer feugiat scelerisque varius morbi enim nunc faucibus a. Mauris ultrices eros in cursus turpis massa tincidunt.\
\
Facilisi etiam dignissim diam quis. Sed nisi lacus sed viverra tellus in hac habitasse platea. Mauris ultrices eros in cursus turpis massa. Consectetur adipiscing elit duis tristique sollicitudin nibh sit amet. Leo vel fringilla est ullamcorper eget nulla facilisi. Eget egestas purus viverra accumsan in nisl nisi. Consequat semper viverra nam libero justo laoreet sit amet cursus. Nec feugiat in fermentum posuere. Ornare massa eget egestas purus. Tempus imperdiet nulla malesuada pellentesque elit eget gravida. Et malesuada fames ac turpis egestas sed tempus. Velit laoreet id donec ultrices. Gravida neque convallis a cras. Mattis pellentesque id nibh tortor id aliquet lectus. Odio ut sem nulla pharetra diam sit amet nisl. Maecenas accumsan lacus vel facilisis.\
\
Senectus et netus et malesuada fames. Odio eu feugiat pretium nibh ipsum. Aliquam purus sit amet luctus venenatis lectus magna fringilla. Accumsan sit amet nulla facilisi morbi tempus. Velit egestas dui id ornare arcu odio ut sem nulla. Scelerisque varius morbi enim nunc faucibus a pellentesque sit. Amet mauris commodo quis imperdiet massa. Ante metus dictum at tempor commodo. At imperdiet dui accumsan sit. Nulla porttitor massa id neque. Aliquet enim tortor at auctor urna nunc id cursus. Tincidunt id aliquet risus feugiat in ante metus dictum at.\
\
Cursus metus aliquam eleifend mi in nulla posuere sollicitudin. Ullamcorper sit amet risus nullam. Turpis in eu mi bibendum neque egestas congue. Elit eget gravida cum sociis. Eu turpis egestas pretium aenean. Suspendisse in est ante in. Malesuada fames ac turpis egestas sed tempus. Molestie ac feugiat sed lectus vestibulum mattis ullamcorper velit sed. Rhoncus aenean vel elit scelerisque mauris. Ipsum suspendisse ultrices gravida dictum fusce ut. Nullam ac tortor vitae purus. Vel quam elementum pulvinar etiam. Cursus metus aliquam eleifend mi. Lorem ipsum dolor sit amet consectetur adipiscing elit pellentesque habitant. Id cursus metus aliquam eleifend mi in nulla posuere. Id velit ut tortor pretium viverra suspendisse potenti nullam ac. Quis risus sed vulputate odio ut enim. Blandit massa enim nec dui nunc mattis enim ut tellus. Molestie nunc non blandit massa. Dignissim cras tincidunt lobortis feugiat.\
\
Quis hendrerit dolor magna eget est lorem ipsum dolor sit. Vitae purus faucibus ornare suspendisse sed nisi lacus sed viverra. Amet commodo nulla facilisi nullam vehicula. Nam libero justo laoreet sit amet cursus sit. Rhoncus est pellentesque elit ullamcorper dignissim. Arcu odio ut sem nulla. Ac felis donec et odio pellentesque diam volutpat commodo sed. Massa sapien faucibus et molestie ac feugiat sed. Malesuada bibendum arcu vitae elementum curabitur vitae nunc. Leo urna molestie at elementum. Amet tellus cras adipiscing enim eu turpis egestas. Varius duis at consectetur lorem. Nulla pharetra diam sit amet nisl suscipit adipiscing bibendum est. Nibh nisl condimentum id venenatis a condimentum vitae sapien pellentesque. Feugiat vivamus at augue eget arcu dictum. Mollis aliquam ut porttitor leo a diam sollicitudin. Sagittis nisl rhoncus mattis rhoncus urna neque viverra justo.");
        BENCHMARK_N(std::stringstream stream(str);
                    vector<std::string> vec(1000);
                    vec.insert(vec.begin() + rand() % 1000,
                               std::istream_iterator<std::string>(stream),
                               std::istream_iterator<std::string>());
                    DO_NOT_OPTIMIZE(vec), 100);
}
