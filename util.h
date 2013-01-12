#ifndef util_w
#define util_w
namespace data {
      template <typename T> T max(T one, T two);
      template <typename T> T min(T one, T two);

      template <typename T> T max(T one, T two) {
            return one > two? one : two;
      }
      template <typename T> T min(T one, T two) {
            return one < two? one: two;
      }
}
#endif
