OBJECTS_CLIENT:=$(patsubst %.cpp,%.o,$(wildcard src/client/*.cpp))
OBJECTS_SERVER:=$(patsubst %.cpp,%.o,$(wildcard src/server/*.cpp))
OBJECTS_COMMON:=$(patsubst %.cpp,%.o,$(wildcard src/common/*.cpp))
OBJECTS:=$(OBJECTS_CLIENT) $(OBJECTS_SERVER) $(OBJECTS_COMMON)

all: voicepipe-client voicepipe-server

voicepipe-client: $(OBJECTS_CLIENT) $(OBJECTS_COMMON)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

voicepipe-server: $(OBJECTS_SERVER) $(OBJECTS_COMMON)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -rf $(OBJECTS) voicepipe-client voicepipe-server
