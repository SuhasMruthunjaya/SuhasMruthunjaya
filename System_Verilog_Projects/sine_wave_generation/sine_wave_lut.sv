module sine_wave_lut (
   input logic [7:0] address,
   output logic [7:0] q
);

always_comb begin
   case (address)
   0: q = 8'h00;
   1: q = 8'h02;
   2: q = 8'h03;
   3: q = 8'h05;
   4: q = 8'h06;
   5: q = 8'h08;
   6: q = 8'h09;
   7: q = 8'h0b;
   8: q = 8'h0c;
   9: q = 8'h0e;
  10: q = 8'h10;
  11: q = 8'h11;
  12: q = 8'h13;
  13: q = 8'h14;
  14: q = 8'h16;
  15: q = 8'h17;
  16: q = 8'h18;
  17: q = 8'h1a;
  18: q = 8'h1b;
  19: q = 8'h1d;
  20: q = 8'h1e;
  21: q = 8'h20;
  22: q = 8'h21;
  23: q = 8'h22;
  24: q = 8'h24;
  25: q = 8'h25;
  26: q = 8'h26;
  27: q = 8'h27;
  28: q = 8'h29;
  29: q = 8'h2a;
  30: q = 8'h2b;
  31: q = 8'h2c;
  32: q = 8'h2d;
  33: q = 8'h2e;
  34: q = 8'h2f;
  35: q = 8'h30;
  36: q = 8'h31;
  37: q = 8'h32;
  38: q = 8'h33;
  39: q = 8'h34;
  40: q = 8'h35;
  41: q = 8'h36;
  42: q = 8'h37;
  43: q = 8'h38;
  44: q = 8'h38;
  45: q = 8'h39;
  46: q = 8'h3a;
  47: q = 8'h3b;
  48: q = 8'h3b;
  49: q = 8'h3c;
  50: q = 8'h3c;
  51: q = 8'h3d;
  52: q = 8'h3d;
  53: q = 8'h3e;
  54: q = 8'h3e;
  55: q = 8'h3e;
  56: q = 8'h3f;
  57: q = 8'h3f;
  58: q = 8'h3f;
  59: q = 8'h40;
  60: q = 8'h40;
  61: q = 8'h40;
  62: q = 8'h40;
  63: q = 8'h40;
  64: q = 8'h40;
  65: q = 8'h40;
  66: q = 8'h40;
  67: q = 8'h40;
  68: q = 8'h40;
  69: q = 8'h40;
  70: q = 8'h3f;
  71: q = 8'h3f;
  72: q = 8'h3f;
  73: q = 8'h3e;
  74: q = 8'h3e;
  75: q = 8'h3e;
  76: q = 8'h3d;
  77: q = 8'h3d;
  78: q = 8'h3c;
  79: q = 8'h3c;
  80: q = 8'h3b;
  81: q = 8'h3b;
  82: q = 8'h3a;
  83: q = 8'h39;
  84: q = 8'h38;
  85: q = 8'h38;
  86: q = 8'h37;
  87: q = 8'h36;
  88: q = 8'h35;
  89: q = 8'h34;
  90: q = 8'h33;
  91: q = 8'h32;
  92: q = 8'h31;
  93: q = 8'h30;
  94: q = 8'h2f;
  95: q = 8'h2e;
  96: q = 8'h2d;
  97: q = 8'h2c;
  98: q = 8'h2b;
  99: q = 8'h2a;
 100: q = 8'h29;
 101: q = 8'h27;
 102: q = 8'h26;
 103: q = 8'h25;
 104: q = 8'h24;
 105: q = 8'h22;
 106: q = 8'h21;
 107: q = 8'h20;
 108: q = 8'h1e;
 109: q = 8'h1d;
 110: q = 8'h1b;
 111: q = 8'h1a;
 112: q = 8'h18;
 113: q = 8'h17;
 114: q = 8'h16;
 115: q = 8'h14;
 116: q = 8'h13;
 117: q = 8'h11;
 118: q = 8'h10;
 119: q = 8'h0e;
 120: q = 8'h0c;
 121: q = 8'h0b;
 122: q = 8'h09;
 123: q = 8'h08;
 124: q = 8'h06;
 125: q = 8'h05;
 126: q = 8'h03;
 127: q = 8'h02;
 128: q = 8'h00;
 129: q = 8'hfe;
 130: q = 8'hfd;
 131: q = 8'hfb;
 132: q = 8'hfa;
 133: q = 8'hf8;
 134: q = 8'hf7;
 135: q = 8'hf5;
 136: q = 8'hf4;
 137: q = 8'hf2;
 138: q = 8'hf0;
 139: q = 8'hef;
 140: q = 8'hed;
 141: q = 8'hec;
 142: q = 8'hea;
 143: q = 8'he9;
 144: q = 8'he8;
 145: q = 8'he6;
 146: q = 8'he5;
 147: q = 8'he3;
 148: q = 8'he2;
 149: q = 8'he0;
 150: q = 8'hdf;
 151: q = 8'hde;
 152: q = 8'hdc;
 153: q = 8'hdb;
 154: q = 8'hda;
 155: q = 8'hd9;
 156: q = 8'hd7;
 157: q = 8'hd6;
 158: q = 8'hd5;
 159: q = 8'hd4;
 160: q = 8'hd3;
 161: q = 8'hd2;
 162: q = 8'hd1;
 163: q = 8'hd0;
 164: q = 8'hcf;
 165: q = 8'hce;
 166: q = 8'hcd;
 167: q = 8'hcc;
 168: q = 8'hcb;
 169: q = 8'hca;
 170: q = 8'hc9;
 171: q = 8'hc8;
 172: q = 8'hc8;
 173: q = 8'hc7;
 174: q = 8'hc6;
 175: q = 8'hc5;
 176: q = 8'hc5;
 177: q = 8'hc4;
 178: q = 8'hc4;
 179: q = 8'hc3;
 180: q = 8'hc3;
 181: q = 8'hc2;
 182: q = 8'hc2;
 183: q = 8'hc2;
 184: q = 8'hc1;
 185: q = 8'hc1;
 186: q = 8'hc1;
 187: q = 8'hc0;
 188: q = 8'hc0;
 189: q = 8'hc0;
 190: q = 8'hc0;
 191: q = 8'hc0;
 192: q = 8'hc0;
 193: q = 8'hc0;
 194: q = 8'hc0;
 195: q = 8'hc0;
 196: q = 8'hc0;
 197: q = 8'hc0;
 198: q = 8'hc1;
 199: q = 8'hc1;
 200: q = 8'hc1;
 201: q = 8'hc2;
 202: q = 8'hc2;
 203: q = 8'hc2;
 204: q = 8'hc3;
 205: q = 8'hc3;
 206: q = 8'hc4;
 207: q = 8'hc4;
 208: q = 8'hc5;
 209: q = 8'hc5;
 210: q = 8'hc6;
 211: q = 8'hc7;
 212: q = 8'hc8;
 213: q = 8'hc8;
 214: q = 8'hc9;
 215: q = 8'hca;
 216: q = 8'hcb;
 217: q = 8'hcc;
 218: q = 8'hcd;
 219: q = 8'hce;
 220: q = 8'hcf;
 221: q = 8'hd0;
 222: q = 8'hd1;
 223: q = 8'hd2;
 224: q = 8'hd3;
 225: q = 8'hd4;
 226: q = 8'hd5;
 227: q = 8'hd6;
 228: q = 8'hd7;
 229: q = 8'hd9;
 230: q = 8'hda;
 231: q = 8'hdb;
 232: q = 8'hdc;
 233: q = 8'hde;
 234: q = 8'hdf;
 235: q = 8'he0;
 236: q = 8'he2;
 237: q = 8'he3;
 238: q = 8'he5;
 239: q = 8'he6;
 240: q = 8'he8;
 241: q = 8'he9;
 242: q = 8'hea;
 243: q = 8'hec;
 244: q = 8'hed;
 245: q = 8'hef;
 246: q = 8'hf0;
 247: q = 8'hf2;
 248: q = 8'hf4;
 249: q = 8'hf5;
 250: q = 8'hf7;
 251: q = 8'hf8;
 252: q = 8'hfa;
 253: q = 8'hfb;
 254: q = 8'hfd;
 255: q = 8'hfe;
endcase
end

endmodule
