# Gym-membership-trainer-management


# New Update :
  + Settings : 
      + Hoàn thiện settings
      + Thêm các themes mới (hiện tại có 9 themes khác nhau)
  + Sort : 
      + Hoàn thiện sort 2 chức năng sort birth_year và registration_date
      + Thêm sort_mode khi sort
          - sort_mode = 0 -> chỉ sort và show
          - sort_mode = 1 -> sort, show và save vào data
  + MemberManagement :
      + Thêm auto_save
          - auto_save = 0 -> không tự động save mà phải save thủ công
          - auto_save = 1 -> save tự động sau mỗi hành động


# Need to Update : 
  + TrainerManagement : 
      + Cần thêm phần kiểm tra auto_save sau mỗi hành động có ảnh hưởng đến data
      + Cần thêm kiểm tra sort_mode sau mỗi khi sort
      + Cải thiện UI
      + Cần update phần assign trainer to member 
      
# Need to Fix : 
  + TrainerManagement : 
      + Các hàm như "add trainer, remove trainer" đang có phần tự động lưu (save_file) nằm ngay bên trong hàm
        -> cần lấy phần save_file đó ra, bỏ vào trainer_menu management chính đi kèm với kiểm tra auto_save từ settings
        -> tối ưu vận hành & mở rộng sau này
      
# Settings Document : 
  + Include : "Settings.h" 
  + Main struct : Settings
  + Variables in struct : 
      int current_auto_save_mode  (0, 1) ~ (not auto save, auto save)
      int current_sort_mode       (0, 1) ~ (just sort, sort & save)
      int current_theme           (0 - 9) ~ (current theme index)


# Conclusion : 
- TrainerManagement cần thêm chức năng mới, tối ưu hóa và cải thiện UI
- Toàn bộ hệ thống cần thống nhất UI giống nhau
