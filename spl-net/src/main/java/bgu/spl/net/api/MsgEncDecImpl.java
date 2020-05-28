package bgu.spl.net.api;

import java.util.Arrays;

public class MsgEncDecImpl implements MessageEncoderDecoder {

    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;

    @Override
    public String decodeNextByte(byte nextByte) {
        if (nextByte == '\u0000') {
            return popString();
        }
        pushByte(nextByte);
        return null;
    }

    @Override
    public byte[] encode(Object message) {
        return (message  + "" + '\u0000').getBytes();
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }
        bytes[len++] = nextByte;
    }

    private String popString() {
        String result = new String(bytes, 0, len);
        len = 0;
        return result;
    }
}
