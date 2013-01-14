Nadia Packet
* Nadia Packet is similar to Redis( Multi Bulk Format )
* Nadia doesn't support inline command

Need Information.
* VectorClock( NodeId, version, timestamp )

Reqeust Packet
```c
#Request Type
enum RequestType {
  GET = 0,
  PUT = 1,
  DELETE = 2,
  INCR = 3,
  DECR = 4
};

struct ClockEntry {
  int32_t node_id;
  int64_t version;
};

struct VectorCock {
  ClockEntry entries;
  int64_t timestamp_;
};

struct Versioned {
  string value;
  VectorClock version;
};

struct KeyedVersions {
  string key;
  Versioned versions;
};

```

```c
#set command


#get command


```

Response Packet

```
#get command

```

