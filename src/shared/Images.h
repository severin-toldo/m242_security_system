class Images {
public:
  static const unsigned char *getLockClosed() { return Images::lock_closed; }

  static const unsigned char *getLockOpen() { return Images::lock_open; }

  static const unsigned char lock_closed[];
  static const unsigned char lock_open[];
};