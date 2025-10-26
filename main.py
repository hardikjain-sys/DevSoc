import groq
import pandas
import json

file = pandas.read_csv('text.txt', header=None)

lines = file[0].tolist()

client = groq.Groq(
    api_key="your_api_key",
)

def reply(x):
    chat_completion = client.chat.completions.create(
        messages=[
            {
                "role": "user",
                    "content": lines[x],
            }
        ],
        model="llama-3.3-70b-versatile",
    )
    return chat_completion.choices[0].message.content
data = []
for i in range(len(lines)):
    print('running')
    data.append({"prompt": lines[i], "reply": reply(i)})


with open('jsonfile.json', 'w') as f:
    json.dump(data, f, indent=4)