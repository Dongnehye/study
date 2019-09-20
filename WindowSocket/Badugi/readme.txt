


// 위완료
// 아래미완료.

로그인 검사
파일 입출력
아이디 패스워드(사용자 :int id, pw, money)

로비서버
vector<int> 8개의 방, int는 방 번호.
vector<id(int)> 로비서버에 존재하는 사용자들 채팅을 위해서 만듬.

채팅
로비에 있는 사람한테만 echo 
방에 있는 사람한테만 echo

게임 바둑좌.


비트맵 자르기  
  static Bitmap GetCardImage(Bitmap cards, int cardnum) {
        int width = cards.Width / 13;
        int height = cards.Height / 4;
        int left = width * (cardnum % 13);
        int top = height * (cardnum % 4);
        var bmp = new Bitmap(width, height,
            System.Drawing.Imaging.PixelFormat.Format32bppPArgb);
        using (var gr = Graphics.FromImage(bmp)) {
            gr.DrawImage(cards,
                new Rectangle(0, 0, width, height),
                new Rectangle(left, top, width, height),
                GraphicsUnit.Pixel);
        }
        return bmp;
    }
You can further extend this by creating an array of bitmaps so you'll have them readily available when you need to draw them. Something you'd do at the splash screen. Let's assume you added the image with the card faces as a resource named CardFaces:

    static Bitmap[] CreateDeckImages() {
        var deck = new Bitmap[52];
        using (var images = Properties.Resources.CardFaces) {
            for (int cardnum = 0; cardnum < deck.Length; ++cardnum) {
                deck[cardnum] = GetCardImage(images, cardnum);
            }
        }
        return deck;
    }
Untested, ought to be close
