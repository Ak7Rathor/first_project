#include <gtest/gtest.h>
#include "Storyboard.cpp" 

class StoryboardTest : public ::testing::Test {
protected:
    Storyboard storyboard;

    void SetUp() override {
        // Intilizialy added
        storyboard.addNote("Title1", "This is the first note.");
        storyboard.addNote("Title2", "This is the second note.");
    }

    void TearDown() override {
        // clean the notes
        storyboard.deleteNote("Title1");
        storyboard.deleteNote("Title2");
    }
};

// new note added 
TEST_F(StoryboardTest, AddNote_ValidInput) {
    EXPECT_TRUE(storyboard.addNote("NewTitle", "This is a new note."));
    auto results = storyboard.searchNoteByTitle("NewTitle");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].text, "This is a new note.");
}


// invalid note provided and check
TEST_F(StoryboardTest, AddNote_InvalidText) {
    EXPECT_FALSE(storyboard.addNote("InvalidTitle", "Invalid@Text#"));
}

// searching by title
TEST_F(StoryboardTest, SearchNoteByTitle) {
    auto results = storyboard.searchNoteByTitle("Title1");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].text, "This is the first note.");
}

// searching by text
TEST_F(StoryboardTest, SearchNoteByText) {
    auto results = storyboard.searchNoteByText("second");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].title, "Title2");
}

//delete notes
TEST_F(StoryboardTest, DeleteNote_ValidTitle) {
    EXPECT_TRUE(storyboard.deleteNote("Title1"));
    auto results = storyboard.searchNoteByTitle("Title1");
    EXPECT_TRUE(results.empty());
}


// Test modifying the title 
TEST_F(StoryboardTest, ModifyNoteTitle_ValidInput) {
    EXPECT_TRUE(storyboard.modifyNoteTitle("Title1", "UpdatedTitle1"));
    auto results = storyboard.searchNoteByTitle("UpdatedTitle1");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].text, "This is the first note.");
}


// modifying the text 
TEST_F(StoryboardTest, ModifyNoteText_ValidInput) {
    EXPECT_TRUE(storyboard.modifyNoteText("Title2", "Updated text for second note."));
    auto results = storyboard.searchNoteByTitle("Title2");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].text, "Updated text for second note.");
}


//  display note
TEST_F(StoryboardTest, DisplayNotes) {
    testing::internal::CaptureStdout();
    storyboard.displayNotes();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Title1"), std::string::npos);
    EXPECT_NE(output.find("Title2"), std::string::npos);
}

// saved and loaded scuessfully or not
TEST_F(StoryboardTest, FilePersistence) {

    storyboard.addNote("Temptitle", "This note is temp");
    
    // load the file
    Storyboard newStoryboard;
    auto results = newStoryboard.searchNoteByTitle("Temptitle");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].text, "This note is temp");

    newStoryboard.deleteNote("Temptitle");
}

