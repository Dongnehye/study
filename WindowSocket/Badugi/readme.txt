


// ���Ϸ�
// �Ʒ��̿Ϸ�.

�α��� �˻�
���� �����
���̵� �н�����(����� :int id, pw, money)

�κ񼭹�
vector<int> 8���� ��, int�� �� ��ȣ.
vector<id(int)> �κ񼭹��� �����ϴ� ����ڵ� ä���� ���ؼ� ����.

ä��
�κ� �ִ� ������׸� echo 
�濡 �ִ� ������׸� echo

���� �ٵ���.


��Ʈ�� �ڸ���  
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
