namespace errors {

template <typename... T>
Error format(fmt::format_string<T...> fmt, T&&... args) {
  return errors::make(fmt::format(fmt, std::forward<T>(args)...));
}

}  // namespace errors
