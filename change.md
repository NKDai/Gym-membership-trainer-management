1. Sửa bugs trong Trainer Management (trainer.c)
   Double-press để exit functions: Thêm clearInputBuffer() sau scanf trong các hàm như addTrainer, editTrainer, deleteTrainer, assignMemberToTrainer, removeMemberFromTrainer.
   Spacing error trong edit name: Sửa scanf(" %[^\n]s", name) thành fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0; trong editTrainer.
   Failures trong view/assign members: Sửa loops từ for (int i = 0; i < trainerCount; i++) thành for (int i = 0; i < currentCapacity; i++) trong displayAllTrainers, searchTrainerById, searchTrainerByName, displayTrainerMembers, assignMemberToTrainer, removeMemberFromTrainer.
   Auto-save: Thêm tm_saveTrainersToFile(trainers, trainerCount); sau mỗi thay đổi (add, edit, delete, assign/remove member).
2. Thêm Screen Clearing trên Menu Changes (trainer.c)
   Thêm Clear(); trong trainerManagementMenu trước displayMenu() và sau mỗi case trong switch (trước Pause();).
3. Thêm File Persistence cho Member Data (MemberManagement.c, MemberManagement.h, main.c)
   Struct MemberManager: Sửa int *members; thành Member *members; trong MemberManagement.h.
   Thêm include: #include "member.h" trong MemberManagement.h.
   Thêm functions: mm_SaveMembersToFile và mm_LoadMembersFromFile trong MemberManagement.c.
   Auto-save trong menu: Thêm mm_SaveMembersToFile sau mm_AddMember, mm_RemoveMember, và sau thay đổi name/membership type trong mm_MemberManagement_ChangeMemberInfo.
   Load trong main: Thêm mm_LoadMembersFromFile(&member_manager); trong main.c sau load trainer.
4. Sửa Compilation Errors
   main.c: Thêm int running = 1; int action; và wrap trong do-while. Sửa MemberManager member_manager = {0, NULL}; và pointer.
   MemberManagement.c: Sửa type mismatches (e.g., members từ int* sang Member*, fix assignments và accesses).
5. Thêm Prefix "tm\_" cho Trainer Functions (trainermag.h, trainer.c, main.c)
   Declarations (trainermag.h): Đổi tất cả hàm từ addTrainer thành tm_addTrainer, etc.
   Definitions (trainer.c): Đổi tên hàm và tất cả calls bên trong (e.g., saveTrainersToFile → tm_saveTrainersToFile).
   Calls (main.c): loadTrainersFromFile → tm_loadTrainersFromFile, trainerManagementMenu → tm_trainerManagementMenu.
6. Kiểm tra Save Tự động cho Member
   Xác nhận save xảy ra trong menu functions (không trong core functions như mm_AddMember).
