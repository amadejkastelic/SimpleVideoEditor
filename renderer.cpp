#include "renderer.h"

uint Renderer::render(const vector<spv::File *> &files, Timeline *timeline) {
    uint length = 0;
    uint layer = 0;
    for (auto && file : files) {
        if (auto* videoFile = dynamic_cast<VideoFile*>(file)) {
            Clip *clip = new Clip(new FFmpegReader(videoFile->GetPath()));
            clip->Position((float) length);
            clip->Start((float) videoFile->GetStart());
            clip->End((float) videoFile->GetEnd());
            clip->gravity = GRAVITY_CENTER;
            clip->scale = videoFile->GetScale();
            clip->Layer(layer++);
            timeline->AddClip(clip);

            if (videoFile->GetAudioFile() != nullptr) {
                Clip *audio = new Clip(new FFmpegReader(videoFile->GetAudioFile()->GetPath()));
                audio->Position((float) length);
                audio->Start((float) videoFile->GetAudioFile()->GetStart());
                audio->End((float) videoFile->GetAudioFile()->GetEnd());
                audio->Layer(layer++);
                clip->volume = 0;
                timeline->AddClip(audio);
            }

            for (Text *text: videoFile->GetText()) {
                auto *font = new QFont(QString::fromStdString(text->GetFont()), text->GetSize(), 1, false);
                Clip *textClip = new Clip(new QtTextReader(1920, 1080, 0, 0, text->GetPosition(), text->GetValue(), *font, "#" + text->GetColor(), "transparent"));
                textClip->Position((float) length);
                textClip->Start(0.0);
                textClip->End((float) videoFile->GetEnd() - videoFile->GetStart());
                textClip->Layer(layer++);
                timeline->AddClip(textClip);
            }

            length += (videoFile->GetEnd() - videoFile->GetStart());
        } else if (auto* imageFile = dynamic_cast<ImageFile*>(file)) {
            if (boost::iequals(imageFile->GetAnimation(), "zoom")) {
                for (size_t i=0; i<imageFile->GetLength()*100; i+=1) {
                    Clip *clip = new Clip(new QtImageReader(imageFile->GetPath()));
                    float x = i/100.0f;
                    clip->Position((float) (length + x));
                    clip->Start(0.0);
                    clip->End(0.01f);
                    clip->gravity = GRAVITY_CENTER;
                    clip->scale = imageFile->GetScale();
                    clip->Layer(layer++);
                    clip->scale_x = Keyframe(1.0 + x/10);
                    clip->scale_y = Keyframe(1.0 + x/10);
                    timeline->AddClip(clip);
                }
            } else {
                Clip *clip = new Clip(new QtImageReader(imageFile->GetPath()));
                clip->Position((float) length);
                clip->Start(0.0);
                clip->End((float) imageFile->GetLength());
                clip->gravity = GRAVITY_CENTER;
                clip->scale = imageFile->GetScale();
                clip->Layer(layer++);
                timeline->AddClip(clip);
            }

            if (imageFile->GetAudioFile() != nullptr) {
                Clip *audio = new Clip(new FFmpegReader(imageFile->GetAudioFile()->GetPath()));
                audio->Position((float) length);
                audio->Start((float) imageFile->GetAudioFile()->GetStart());
                audio->End((float) imageFile->GetLength() + audio->Start());
                audio->Layer(layer++);
                timeline->AddClip(audio);
            }

            for (Text *text: imageFile->GetText()) {
                auto *font = new QFont(QString::fromStdString(text->GetFont()), text->GetSize(), 1, false);
                Clip *textClip = new Clip(new QtTextReader(1920, 1080, 0, 0, text->GetPosition(), text->GetValue(), *font, text->GetColor(), "transparent"));
                textClip->Position((float) length);
                textClip->Start(0.0);
                textClip->End((float) imageFile->GetLength());
                textClip->Layer(layer++);
                timeline->AddClip(textClip);
            }

            length += imageFile->GetLength();
        }
    }

    return length;

    //timeline.Open();

    /*FFmpegWriter writer("/home/amadejk/test.webm");
    writer.SetAudioOptions(true, "libvorbis", 44100, 2, ChannelLayout::LAYOUT_STEREO, 128000);
    writer.SetVideoOptions(true, "libvpx", Fraction(24,1), 1920, 1080, Fraction(1,1), false, false, 300000);
    writer.Open();

    int64_t loc = 1;
    while (loc < length * 24) {
        shared_ptr<Frame> frame = timeline.GetFrame(loc);
        writer.WriteFrame(frame);
        loc++;
    }

    writer.Close();*/
    //timeline.Close();
}
