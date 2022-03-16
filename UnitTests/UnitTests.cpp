#include "CppUnitTest.h"

#include "../OneArmedBandit/Player.h"
#include "../OneArmedBandit/GameData.h"
#include "../OneArmedBandit/SlotMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(SlotMachineMoney)
    {
    public:

        // Small amount of money
        TEST_METHOD(Play1)
        {
            SlotMachine game;
            Player player(10);

            auto [slots, victory, out_of_money] = game.Play(player);

            Assert::IsNotNull(slots);
            Assert::IsFalse(out_of_money);
        }

        // No money
        TEST_METHOD(Play2)
        {
            SlotMachine game;
            Player player(0);

            auto [slots, victory, out_of_money] = game.Play(player);

            Assert::IsNotNull(slots);
            Assert::IsTrue(out_of_money);
        }

        // Very large amount of money
        TEST_METHOD(Play3)
        {
            SlotMachine game;
            Player player(1'000'000'000);

            auto [slots, victory, out_of_money] = game.Play(player);

            Assert::IsNotNull(slots);
            Assert::IsFalse(out_of_money);
        }

        // No money, default constructed
        TEST_METHOD(Play4)
        {
            SlotMachine game;
            Player player{};

            auto [slots, victory, out_of_money] = game.Play(player);

            Assert::IsNotNull(slots);
            Assert::IsTrue(out_of_money);
        }

        // Negative money
        TEST_METHOD(Play5)
        {
            SlotMachine game;
            Player player(-1'000);

            auto [slots, victory, out_of_money] = game.Play(player);

            Assert::IsNotNull(slots);
            Assert::IsTrue(out_of_money);
        }
    };

    TEST_CLASS(SlotMachineVictory)
    {
    public:
        // Test if victory possible in reasonable likeliness
        TEST_METHOD(Play1)
        {
            SlotMachine game;
            Player player(1'000);

            int abort = 0;
            bool was_true = false;
            while (player.money && abort < 1'000'000) {
                ++abort;

                auto [slots, victory, out_of_money] = game.Play(player);

                if (victory) {
                    was_true = true;
                    break;
                }
            }

            Assert::IsTrue(was_true);
        }

        // Test if victory possible, huge jackpot
        TEST_METHOD(Play2)
        {
            SlotMachine game(1'000'000'000);
            Player player(1'000);

            int abort = 0;
            bool was_true = false;
            while (player.money && abort < 1'000'000) {
                ++abort;

                auto [slots, victory, out_of_money] = game.Play(player);

                if (victory) {
                    was_true = true;
                    break;
                }
            }

            Assert::IsTrue(was_true);
        }

        // Test if victory possible, no jackpot
        TEST_METHOD(Play3)
        {
            SlotMachine game(0);
            Player player(1'000);

            int abort = 0;
            bool was_true = false;
            while (player.money && abort < 1'000'000) {
                ++abort;

                auto [slots, victory, out_of_money] = game.Play(player);

                if (victory) {
                    was_true = true;
                    break;
                }
            }

            Assert::IsTrue(was_true);
        }

        // Test if victory possible, invalid jackpot
        TEST_METHOD(Play4)
        {
            SlotMachine game(-1);
            Player player(1'000);

            int abort = 0;
            bool was_true = false;
            while (player.money && abort < 1'000'000) {
                ++abort;

                auto [slots, victory, out_of_money] = game.Play(player);

                if (victory) {
                    was_true = true;
                    break;
                }
            }

            Assert::IsTrue(was_true);
        }
    };

    TEST_CLASS(Data)
    {
    public:
        // Test if colour code mappings are as expected
        TEST_METHOD(Mappings)
        {
            Assert::AreEqual(slot_mappings.at(static_cast<Colour>(0)).c_str(), "Black");
            Assert::AreEqual(slot_mappings.at(static_cast<Colour>(1)).c_str(), "White");
            Assert::AreEqual(slot_mappings.at(static_cast<Colour>(2)).c_str(), "Green");
            Assert::AreEqual(slot_mappings.at(static_cast<Colour>(3)).c_str(), "Yellow");
        }
    };
}
