--- Created by sola.
--- DateTime: 2023/10/4

print("lua start")

local stu = MyModule.Student(18, "Akuya")

print(stu:GetName())
stu:ShowSelfInfo()

stu:SetAge(17)
stu:SetName("Megumin")
stu:ShowSelfInfo()

print("lua end")