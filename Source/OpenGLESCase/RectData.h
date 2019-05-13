//
// Created by liuqian8 on 2019/5/13.
//

#pragma once

struct RectScreen
{
    float positions[8]=
            {
                    1,1,
                    1,-1,
                    -1,-1,
                    -1,1
            };
    float texcoords[8] =
            {
                    1,1,
                    1,0,
                    0,0,
                    0,1
            };
    int index[6] =
            {
                    0,1,2,
                    0,2,3
            };
};
