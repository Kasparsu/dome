// Represents the data of an audio file
// which can be loaded
// It is otherwise opaque Wren-side

foreign class AudioData {
  construct init(buffer) {}
  static load(path) {
    import "io" for FileSystem
    var data = AudioData.init(FileSystem.load(path))
    System.print("Audio loaded: " + path)
    return data
  }
  foreign length
}

class AudioState {
  static INITIALIZE { 1 }
  static TO_PLAY { 2 }
  static DEVIRTUALIZE { 3 }
  static LOADING { 4 }
  static PLAYING { 5 }
  static STOPPING { 6 }
  static STOPPED { 7 }
  static VIRTUALIZING { 8 }
  static VIRTUAL { 9 }
}

// Base interface for audio channels
class AudioChannel {}

// Encapsulates the data of the currently playing channel
foreign class SystemChannel is AudioChannel {
  construct new(soundId) {
    // Sensible defaults
    volume = 1
    pan = 0
    loop = false
  }
  foreign audio=(value)

  foreign length
  foreign soundId
  foreign id
  foreign position
  foreign position=(v)

  foreign state
  foreign state=(value)

  foreign loop=(do)
  foreign loop

  foreign pan=(pan)
  foreign pan

  foreign volume=(volume)
  foreign volume

  foreign stop()

  finished { state == AudioState.STOPPED }
}

class AudioEngine {
  // TODO: Allow device enumeration and selection
  static init() {
    __nameMap = {}
    __files = {}
    __channels = {}
  }

  static register(name, path) {
    __nameMap[name] = path
  }

  static load(name, path) {
    register(name, path)
    return load(name)
  }

  static load(name) {
    if (!__nameMap.containsKey(name)) {
      Fiber.abort("Audio '%(name)' has not been registered ")
    }
    var path = __nameMap[name]
    if (!__files.containsKey(path)) {
      __files[path] = AudioData.load(path)
    }
    return __files[path]
  }

  static unload(name) {
    var path = __nameMap[name]
    __files.remove(path)
    System.gc()
  }

  static unloadAll() {
    __nameMap.keys.each {|key| unload(key) }
  }

  static play(name) { play(name, 1, false, 0) }
  static play(name, volume) { play(name, volume, false, 0) }
  static play(name, volume, loop) { play(name, volume, loop, 0) }
  static play(name, volume, loop, pan) {
    var channel = SystemChannel.new(name)
    channel.audio = load(name)
    channel.volume = volume
    channel.pan = pan
    channel.loop = loop
    __channels[channel.id] = channel
    return channel
  }

  static stopAllChannels() {
    f_stopAllChannels()
  }

  foreign static f_stopAllChannels()
}
AudioEngine.init()
