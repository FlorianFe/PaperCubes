{
"targets": [
{
    "target_name": "binding",
    "sources":
    [
        "Minecraft-Orthogami/main.cpp",
        "<!@(node -p \"require('fs').readdirSync('./Minecraft-Orthogami').map(f=>'Minecraft-Orthogami/'+f).join(' ')\")"
    ],
    'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
}
]
}
