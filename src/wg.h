#define WG_NOISE_PUBLIC_KEY_LEN 32
#define WG_COOKIE_LEN           16
#define WG_NOISE_TIMESTAMP_LEN  12
#define WG_NOISE_AUTHTAG_LEN    16
#define WG_COOKIE_NONCE_LEN     24

#define wg_noise_encrypted_len(plain_len) ((plain_len) + WG_NOISE_AUTHTAG_LEN)

struct wg_message_header {
	__le32 type;
};

struct wg_message_macs {
	u8 mac1[WG_COOKIE_LEN];
	u8 mac2[WG_COOKIE_LEN];
};

struct wg_message_handshake_initiation {
	struct wg_message_header header;
	__le32 sender_index;
	u8 unencrypted_ephemeral[WG_NOISE_PUBLIC_KEY_LEN];
	u8 encrypted_static[wg_noise_encrypted_len(WG_NOISE_PUBLIC_KEY_LEN)];
	u8 encrypted_timestamp[wg_noise_encrypted_len(WG_NOISE_TIMESTAMP_LEN)];
	struct wg_message_macs macs;
};

struct wg_message_handshake_response {
	struct wg_message_header header;
	__le32 sender_index;
	__le32 receiver_index;
	u8 unencrypted_ephemeral[WG_NOISE_PUBLIC_KEY_LEN];
	u8 encrypted_nothing[wg_noise_encrypted_len(0)];
	struct wg_message_macs macs;
};
