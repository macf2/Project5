#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>


class Cat
{
public:
        Cat()
        {
                i = -1;
        }

        Cat(
                uint32_t i,
                char *pbreed, 
                uint32_t age, 
                uint32_t weight, 
                uint32_t idx_color, 
                uint32_t idx_gender) 
        {
                this->i = i;
                this->pbreed = pbreed;
                this->age = age;
                this->weight = weight;
                this->idx_color = idx_color;
                this->idx_gender = idx_gender;
        }

        uint32_t get_id() const;
        char *get_pbreed() const;
        uint32_t get_age() const;
        uint32_t get_weight() const;
        char *get_pcolor() const;
        char *get_pgender() const;

        void print();

        void set_breed(char *ptr);
        void set_age(uint32_t age);
        void set_weight(uint32_t weight);
        void set_color(char *ptr);
        void set_gender(char *ptr);

        bool operator==(const Cat &b) const 
        {
                return get_age() == b.get_age();
        }

        bool operator<(const Cat &b) const
        {
                return get_age() < b.get_age();
        }

        bool operator>(const Cat &b) const
        {
                return get_age() > b.get_age();
        }

        bool operator<=(const Cat &b) const
        {
                return get_age() <= b.get_age();
        }

        bool operator>=(const Cat &b) const
        {
                return get_age() >= b.get_age();
        }


private:
        uint32_t i;
        char *pbreed;
        uint32_t age, weight; 
        uint32_t idx_color;
        uint32_t idx_gender;
};

char *Cat::get_pbreed() const
{
        return pbreed;
}

uint32_t Cat::get_age() const
{
        return age;
}

uint32_t Cat::get_weight() const
{
        return weight;
}

char *Cat::get_pcolor() const
{
        return &pbreed[idx_color];
}

char *Cat::get_pgender() const
{
        return &pbreed[idx_gender];
}

uint32_t Cat::get_id() const
{
        return i;
}

void Cat::set_breed(char *ptr)
{
        if (!ptr)
                return;

        pbreed = ptr;
}

void Cat::set_age(uint32_t a) 
{
        age = a;
}

void Cat::set_weight(uint32_t w)
{
        weight = w;
}

void Cat::set_color(char *ptr)
{
        if (!ptr)
                return;

        strcpy(get_pcolor(), ptr);
}

void Cat::set_gender(char *ptr)
{
        if (!ptr)
                return;

        strcpy(get_pgender(), ptr);
}


void Cat::print()
{
        if (i == -1)
        {
                return;
        }
        printf("\nCat #%d:\n", get_id());
        printf("Breed: %s\n", get_pbreed());
        printf("Age: %d\n", get_age());
        printf("Weight: %d\n", get_weight());
        printf("Color: %s\n", get_pcolor());
        printf("Gender: %s\n", get_pgender());
}
