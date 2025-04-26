import { fileURLToPath, URL } from 'node:url'
import vue from '@vitejs/plugin-vue'
// @ts-expect-error
import AutoImport from 'unplugin-auto-import/vite'
// @ts-expect-error
import Components from 'unplugin-vue-components/vite'
// @ts-expect-error
import { NaiveUiResolver } from 'unplugin-vue-components/resolvers'
import { defineConfig } from 'vite'


// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
    AutoImport({
      imports: [
        'vue',
        {
          'naive-ui': [
            'useDialog',
            'useMessage',
            'useNotification',
            'useLoadingBar'
          ]
        }
      ]
    }),
    Components({
      resolvers: [NaiveUiResolver()]
    })
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  }
})
