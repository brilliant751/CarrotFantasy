#pragma once
const Vec2 origin = Vec2(240, 100); //��ͼ�������
Vec2 get_po(int line, int row);
int get_line(float y);
int get_row(float x);
int get_tag_waves(int tag);
void update_tag(int& tag, int waves);
