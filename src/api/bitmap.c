internal DOME_Bitmap*
BITMAP_API_fromFileInMemory(DOME_Context ctx, void* buffer, size_t length) {
  DOME_Bitmap* bitmap = malloc(sizeof(DOME_Bitmap));
  if (bitmap == NULL) {
    char* reason = strerror(errno);
    size_t length = strlen(reason) + 1;
    PLUGIN_COLLECTION_setErrorReason((ENGINE*)ctx, reason, length);
    return NULL;
  }

  bitmap->pixels = (DOME_Color*)stbi_load_from_memory((const stbi_uc*)buffer, length,
      &bitmap->width, &bitmap->height,
      &bitmap->channels, STBI_rgb_alpha);
  if (bitmap->pixels == NULL) {
    free(bitmap);
    bitmap = NULL;
    const char* reason = stbi_failure_reason();
    size_t length = strlen(reason) + 1;
    PLUGIN_COLLECTION_setErrorReason((ENGINE*)ctx, reason, length);
  }
  return bitmap;
}

internal DOME_Bitmap*
BITMAP_API_fromFile(DOME_Context ctx, const char* path) {
  size_t length;
  void* buffer = IO_API_readFile(ctx, path, &length);
  return BITMAP_API_fromFileInMemory(ctx, buffer, length);
}

internal DOME_Color
BITMAP_API_pget(DOME_Bitmap* bitmap, uint32_t x, uint32_t y) {
  assert(y < bitmap->height);
  assert(x < bitmap->width);
  return bitmap->pixels[y * bitmap->width + x];
}

internal void
BITMAP_API_pset(DOME_Bitmap* bitmap, uint32_t x, uint32_t y, DOME_Color color) {
  assert(y < bitmap->height);
  assert(x < bitmap->width);
  bitmap->pixels[y * bitmap->width + x] = color;
}

internal void
BITMAP_API_free(DOME_Bitmap* bitmap) {
  if (bitmap->pixels != NULL) {
    free(bitmap->pixels);
  }
  free(bitmap);
}

BITMAP_API_v0 bitmap_v0 = {
  .fromFileInMemory = BITMAP_API_fromFileInMemory,
  .fromFile = BITMAP_API_fromFile,
  .pget = BITMAP_API_pget,
  .pset = BITMAP_API_pset,
  .free = BITMAP_API_free
};

