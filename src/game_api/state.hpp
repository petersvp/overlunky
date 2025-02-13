#pragma once

#include "items.hpp"
#include "layer.hpp"
#include "memory.hpp"
#include "savedata.hpp"
#include "thread_utils.hpp"

const float ZF = 0.737;

struct Layer;

struct StateMemory
{
    size_t p00;
    uint32_t screen_last;
    uint32_t screen;
    uint32_t screen_next;
    uint32_t loading;
    size_t p18;
    int32_t i20;
    uint32_t fadeout;
    uint32_t fadein;
    int32_t i2c;
    uint8_t ingame;
    uint8_t playing;
    uint8_t pause;
    uint8_t b33;
    int32_t i34;
    uint32_t quest_flags;
    int32_t i3c;
    int32_t i40;
    int32_t i44;
    uint32_t w;
    uint32_t h;
    int8_t kali_favor;
    int8_t kali_status;
    int8_t kali_altars_destroyed;
    uint8_t b4f;
    int32_t i50;
    int32_t i54;
    uint8_t world_start;
    uint8_t level_start;
    uint8_t theme_start;
    uint8_t b5f;
    uint32_t seed;
    uint32_t time_total;
    uint8_t world;
    uint8_t world_next;
    uint8_t level;
    uint8_t level_next;
    int32_t i6c;
    int32_t i70;
    uint8_t theme;
    uint8_t theme_next;
    uint8_t b72;
    uint8_t b73;
    int32_t i74;
    uint8_t shoppie_aggro;
    uint8_t shoppie_aggro_levels;
    uint8_t merchant_aggro;
    uint8_t saved_dogs;
    uint8_t saved_cats;
    uint8_t saved_hamsters;
    uint8_t kills_npc;
    uint8_t level_count;
    uint8_t pad84[0x970];
    uint32_t journal_flags;
    int32_t i9f0;
    int32_t i9f4;
    uint32_t time_last_level;
    uint32_t time_level;
    int32_t ia00;
    int32_t ia04;
    int32_t hud_flags;

    char pada14[0x12b0 - 0xa14];
    Items *items;
    void *pad12b8;
    Layer *layers[2];
    char pad12d0[0x1308 - 0x12d0];
    std::unordered_map<uint32_t, Entity *> instance_id_to_pointer;
};
struct State
{
    size_t location;
    size_t addr_damage;
    size_t addr_insta;
    size_t addr_zoom;
    size_t addr_zoom_shop;
    size_t addr_dark;

    static State &get();

    StateMemory *ptr() const;

    Layer *layer(uint8_t index)
    {
        return ptr()->layers[index];
    }

    Items *items()
    {
        auto pointer = ptr()->items;
        return (Items *)(pointer);
    }

    void godmode(bool g)
    {
        // log::debug!("God {:?}" mode; g);
        if (g)
        {
            write_mem_prot(addr_damage, ("\xC3"s), true);
            write_mem_prot(addr_insta, ("\xC3"s), true);
        }
        else
        {
            write_mem_prot(addr_damage, ("\x48"s), true);
            write_mem_prot(addr_insta, ("\x40"s), true);
        }
    }

    void darkmode(bool g)
    {
        // log::debug!("God {:?}" mode; g);
        if (g)
        {
            write_mem_prot(addr_dark, ("\x90\x90"s), true);
        }
        else
        {
            write_mem_prot(addr_dark, ("\xEB\x2E"s), true);
        }
    }

    void zoom(float level)
    {
        // This technically sets camp zoom but not interactively :(
        // auto addr_zoom = find_inst(memory.exe(), &hex!("C7 80 E8 04 08 00"),
        // memory.after_bundle); write_mem_prot(memory.at_exe(addr_zoom + 6),
        // to_le_bytes(level), true); addr_zoom = memory.after_bundle;

        uint8_t roomx = ptr()->w;
        if (level == 0.0)
        {
            switch (roomx)
            {
            case 1:
                level = 9.50;
                break;
            case 2:
                level = 16.29;
                break;
            case 3:
                level = 23.08;
                break;
            case 4:
                level = 29.87;
                break;
            case 5:
                level = 36.66;
                break;
            case 6:
                level = 43.45;
                break;
            case 7:
                level = 50.24;
                break;
            case 8:
                level = 57.03;
                break;
            default:
                level = 13.5;
            }
        }
        write_mem_prot(addr_zoom, to_le_bytes(level), true);
        write_mem_prot(addr_zoom_shop, to_le_bytes(level), true);
    }

    std::pair<float, float> click_position(float x, float y);
    std::pair<float, float> screen_position(float x, float y);
    float get_zoom_level();

    uint32_t flags()
    {
        return ptr()->hud_flags;
    }

    void set_flags(uint32_t f)
    {
        ptr()->hud_flags = f;
    }

    void set_pause(uint8_t p)
    {
        ptr()->pause = p;
    }

    uint32_t get_frame_count()
    {
        return read_u32((size_t)ptr() - 0xd0);
    }

    std::vector<int64_t> read_prng()
    {
        std::vector<int64_t> prng;
        for (int i = 0; i < 20; ++i)
        {
            prng.push_back(read_i64((size_t)ptr() - 0xb0 + 8 * i));
        }
        return prng;
    }

    Entity *find(uint32_t unique_id)
    {
        auto &map = ptr()->instance_id_to_pointer;
        auto it = map.find(unique_id);
        if (it == map.end())
            return nullptr;
        return it->second;
    }

    std::pair<float, float> get_camera_position();
    void set_camera_position(float cx, float cy);
    void warp(uint8_t w, uint8_t l, uint8_t t);
    void set_seed(uint32_t seed);
    SaveData *savedata();
};
