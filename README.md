**Giới thiệu game**

Flappy Bird là một trò chơi điện tử đơn giản nhưng gây nghiện, nơi người
chơi điều khiển một chú chim nhỏ bay qua các ống cản trở bằng cách nhấn
vào màn hình. Mục tiêu của trò chơi là bay càng xa càng tốt mà không va
vào các ống, đồng thời ghi điểm cao nhất có thể. Với đồ họa pixel dễ
thương và gameplay dễ tiếp cận, Flappy Bird mang đến những phút giây
giải trí vui nhộn và thách thức. Hãy cùng thử thách để xem bạn được bao
nhiêu điểm nào!

**0.1 Cách tải game**

**a, Cách 1: Không bao gồm mã**

- Tải game (được nén thành .zip) tại link
sauhttps://github.com/noname7749/BTL\_Lap\_Trinh\_Nang\_Cao

>-  Cách này tiết kiệm bộ nhớ và thời gian tải đi rất nhiều.
>-  Giải nén trò chơi vào một thư mục và bật FB.exe lên và chơi.

**b, Cách 2: Bao gồm mã và có thể biên dịch**

- Bước 1:  Clone repo này hoặc chọn Code -&gt; Download Zip 

![A black screen with white text Description automatically
generated](media/image1.png){width="6.268055555555556in"
height="0.9048611111111111in"}

- Bước 2: Mở ứng dụng Visual Studio Community 2022.

- Bước 3: Cài đặt thư viện SDL2 cho Visual Studio Code theo hướng dẫn:
<https://youtu.be/UgJadfInqyo?si=vM9j9muNemKnXCGr>

- Bước 4: Mở file game Flappybird.sln bằng Visual Studio Code.

- Bước 5: Ấn phím F5 để chạy game.

**1. Bắt đầu trò chơi**

- Đợi một chút rồi click vào nút “Start Game” để bắt đầu trò chơi.

![A cartoon bird on a pole Description automatically
generated](media/image2.png){width="6.268055555555556in"
height="3.136111111111111in"}

**2. Các thành phần trong game**

- Chim![](media/image3.png){width="0.718850612423447in"
height="0.4896511373578303in"}: nhân vật chú chim mà bạn cần điều khiển
để vượt qua nhiều chướng ngại vật để có thể giành được số điểm cao nhất
có thể.

- Chim khi rơi xuống đất
![](media/image4.png){width="0.6667596237970254in"
height="0.4792333770778653in"}: chú chim của bạn sẽ chết khi chạm đất
hoặc đâm vào tường

- Ống cống ![A yellow rectangular object with a black background
Description automatically
generated](media/image5.png){width="2.0211154855643043in"
height="2.344076990376203in"} : bạn cần đi qua khe giữa 2 cột để ghi
điểm

- Nền ![A blue sky with clouds Description automatically
generated](media/image6.png){width="3.27128937007874in"
height="1.7294083552055992in"}

- Ảnh nền hiển thị điểm số hiện tại và best score ![A video game screen
with grass and clouds Description automatically
generated](media/image7.png){width="3.3129625984251967in"
height="1.7606627296587927in"}

- Ảnh nền khi game over ![A video game screen with a green bird and a pipe
Description automatically
generated](media/image8.png){width="3.323380358705162in"
height="1.7294083552055992in"}

- Đất ![](media/image9.png){width="2.614948600174978in"
height="0.1771084864391951in"}

- Ảnh nền menu game![A cartoon bird on a pole Description automatically
generated](media/image10.png){width="3.3025437445319334in"
height="1.6460629921259842in"}

**3. Cách chơi**

- Các phím tắt trong game:

  - Phím mũi tên(↑): ấn để giúp chú chim bay lên cao để tránh va chạm vào
ống nước hay rơi xuống đất.

  - Phím cách(SPACE): ấn để tạm dừng trò chơi, ấn thêm lần nữa để tiếp tục.

- Cách chơi: Mục tiêu của trò chơi Flappy Bird là giúp cho con chim đạt
được số điểm cao nhất có thể. Người chơi điều khiển con chim bằng cách
nhấp nút mũi tên để khiến nó bay lên, nhằm vượt qua các vật cản là ống
cống màu xanh. Mỗi lần ấn phím, con chim sẽ cất cánh lên và sau đó rơi
xuống do trọng lực, và người chơi cần phải điều chỉnh nhịp nhấp chuột để
giữ cho con chim không va vào các vật cản. Điểm số được tính bằng cách
vượt qua các cặp ống cống mà không chạm vào chúng. Trò chơi mang đến một
thử thách thú vị với cơ chế điều khiển đơn giản nhưng đòi hỏi sự khéo
léo và phản xạ nhanh nhạy. Bạn có thể đoán được điều gì chờ bạn và chú
chim của bạn ở cuối con đường không? Cùng chinh phục thử thách này nhé!

![](media/image11.png){width="2.8776006124234472in"
height="1.3712128171478566in"}![A video game screen with clouds and blue
sky Description automatically
generated](media/image12.png){width="2.8405883639545055in"
height="1.3699398512685914in"}

- Khi bắt đầu trò chơi sẽ xuất hiện bộ đếm “3, 2, 1, READY, GO!”
- Khi chú chim của bạn chết, một màn hình sẽ hiện lên và hiển thị điểm của
bạn trong ván vừa rồi và điểm cao
nhất![](media/image13.png){width="6.268055555555556in"
height="3.1458333333333335in"}

**4. Các kĩ thuật sử dụng**

- Sử dụng thư viện SDL2: SDL2 được sử dụng để quản lý đồ họa, xử lý sự
kiện, và hiển thị các đối tượng trong game. Thư viện này cung cấp các
chức năng để tạo cửa sổ, vẽ hình ảnh, và xử lý sự kiện người dùng.

- Sử dụng Class

  - BaseObject: Quản lý các đối tượng cơ bản như hình nền và mặt đất. Chứa
 các phương thức để tải và hiển thị hình ảnh.\
  - PlayerObject: Quản lý hành vi của con chim, bao gồm việc di chuyển và
 xử lý sự kiện người dùng như nhấn phím để bay.\
    - BlockManager: Quản lý các vật cản (thân cây), bao gồm việc sinh ra, di
    chuyển, và kiểm tra va chạm với con chim.\
  - TextObject: Quản lý việc hiển thị văn bản trên màn hình, bao gồm điểm
  số và các thông báo khác.\
  -  HighScoreManager: Quản lý danh sách điểm cao, cập nhật và lưu trữ điểm số cao nhất.

- Xử lí va chạm

-  Kiểm tra va chạm giữa con chim với các ống nước và mắt đất.

-  Kiểm tra va chạm giữa các đối tượng với biên giới của cửa sổ game.
>
 - Xử lí trọng lực và chuyển động
>
 - Áp dụng trọng lực cho con chim, khiến nó rơi tự do khi không nhấn mũi tên lên
>
-  Tạo chuyển động cho các ống nước di chuyển từ phải sang trái.
>
- Tạo và sử dụng hiệu ứng âm thanh:
>
> - Phát nhạc nền, âm thanh phát ra khi va chạm, bay lên, game over
>
> - Xử lí giao diện người dùng
>
> - Tạo các nút như: “start game”, “quit”
>
>- Hiển thị văn bản như: điểm số, bắt đầu game, kỉ lục

**5. Nguồn tham khảo**
- Web tutorial SDL2: [Link](https://phattrienphanmem123az.com/lap-trinh-game-c-p2)
- Mã nguồn tham khảo: [Link](https://drive.google.com/file/d/1ru5ppPdtNbaqDJVK5a4j0NCl_hL__KsM/view)
- Bản quyền game gốc của Nguyễn Hà Đông(2013)
- Hình ảnh và âm thanh được tham khảo từ [Link](https://drive.google.com/file/d/1ru5ppPdtNbaqDJVK5a4j0NCl_hL__KsM/view) và google.
- Co

**6. 